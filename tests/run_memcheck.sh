#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT=$(cd "$(dirname "$0")/.." && pwd)
cd "$REPO_ROOT"

BIN_MAIN="$REPO_ROOT/cube3D"
BIN_TEST="$REPO_ROOT/cube3D_tests"
LOG_ROOT="$REPO_ROOT/tests"
OUT_DIR="$LOG_ROOT/memcheck_logs"

mkdir -p "$OUT_DIR"

if [ ! -x "$BIN_MAIN" ]; then
	echo "Executable '$BIN_MAIN' manquant. Lance 'make' avant memcheck." >&2
	exit 1
fi
if [ ! -x "$BIN_TEST" ]; then
	echo "Executable '$BIN_TEST' manquant. Lance 'make test' avant memcheck." >&2
	exit 1
fi

SCENARIOS=(
	"unit_tests|success|$BIN_TEST"
	"map_small|success|$BIN_MAIN map/map_1.cub"
	"map_dust2|failure|$BIN_MAIN map/dust_2.cub"
	"missing_argument|failure|$BIN_MAIN"
	"bad_extension|failure|$BIN_MAIN map/no_ext.pnasdg"
	"no_config_section|failure|$BIN_MAIN map/no_config.cub"
	"no_map_section|failure|$BIN_MAIN map/no_map.cub"
	"no_player|failure|$BIN_MAIN map/no_player.cub"
	"multiple_players|failure|$BIN_MAIN map/no_single_player.cub"
	"gnl_stress|failure|$BIN_MAIN map/gnl_leak.cub"
)

sanitize() {
	echo "$1" | tr '[:upper:]' '[:lower:]' | tr -c 'a-z0-9_' '_'
}

check_expectation() {
	local label=$1
	local expectation=$2
	local exit_code=$3
	if [ "$expectation" = "success" ] && [ "$exit_code" -ne 0 ]; then
		echo "[$label] attendu succès mais code $exit_code" >&2
		return 1
	fi
	if [ "$expectation" = "failure" ] && [ "$exit_code" -eq 0 ]; then
		echo "[$label] attendu échec mais code 0" >&2
		return 1
	fi
	return 0
}

run_valgrind_case() {
	local label=$1
	local expectation=$2
	shift 2
	local -a cmd=("$@")
	local safe_label=$(sanitize "$label")
	local program_log="$OUT_DIR/${safe_label}.out"
	local vg_log="$OUT_DIR/valgrind_${safe_label}.log"
	local exit_code
	if valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=97 \
		--log-file="$vg_log" "${cmd[@]}" >"$program_log" 2>&1; then
		exit_code=0
	else
		exit_code=$?
	fi
	local status=0
	if ! grep -q "definitely lost: 0 bytes" "$vg_log" || \
		! grep -q "indirectly lost: 0 bytes" "$vg_log" || \
		! grep -q "ERROR SUMMARY: 0 errors" "$vg_log"; then
		echo "[$label] fuites détectées par valgrind. Voir $vg_log" >&2
		status=1
	fi
	if ! check_expectation "$label" "$expectation" "$exit_code"; then
		status=1
	fi
	return $status
}

run_leaks_case() {
	local label=$1
	local expectation=$2
	shift 2
	local -a cmd=("$@")
	local safe_label=$(sanitize "$label")
	local program_log="$OUT_DIR/${safe_label}.out"
	local leaks_log="$OUT_DIR/leaks_${safe_label}.log"
	local tmp_log
	local exit_code
	if "${cmd[@]}" >"$program_log" 2>&1; then
		exit_code=0
	else
		exit_code=$?
	fi
	local status=0
	if ! check_expectation "$label" "$expectation" "$exit_code"; then
		status=1
	fi
	tmp_log=$(mktemp "$OUT_DIR/leaks_${safe_label}.XXXXXX")
	if leaks -quiet --atExit -- "${cmd[@]}" >"$tmp_log" 2>&1; then
		:
	else
		echo "[$label] commande 'leaks' a échoué. Voir $tmp_log" >&2
		rm -f "$tmp_log"
		return 1
	fi
	mv "$tmp_log" "$leaks_log"
	if ! grep -q "0 leaks for 0 total leaked bytes" "$leaks_log"; then
		echo "[$label] fuites signalées par 'leaks'. Voir $leaks_log" >&2
		status=1
	fi
	return $status
}

tool=""
if command -v valgrind >/dev/null 2>&1; then
	tool="valgrind"
elif command -v leaks >/dev/null 2>&1; then
	tool="leaks"
else
	echo "Ni valgrind ni leaks disponibles; memcheck impossible." >&2
	exit 0
fi

total=0
ok=0
global_status=0

for entry in "${SCENARIOS[@]}"; do
	IFS='|' read -r label expectation cmdline <<<"$entry"
	read -r -a cmd <<<"$cmdline"
	total=$((total + 1))
	echo "→ [$tool] $label (${expectation})"
	if [ "$tool" = "valgrind" ]; then
		if run_valgrind_case "$label" "$expectation" "${cmd[@]}"; then
			echo "  ✓ aucun leak"
			ok=$((ok + 1))
		else
			echo "  ✗ problème détecté" >&2
			global_status=1
		fi
	else
		if run_leaks_case "$label" "$expectation" "${cmd[@]}"; then
			echo "  ✓ aucun leak"
			ok=$((ok + 1))
		else
			echo "  ✗ problème détecté" >&2
			global_status=1
		fi
	fi
done

echo
echo "$ok/$total scénarios sans fuite rapportée. Logs: $OUT_DIR"
exit $global_status
