#include "cube.h"
#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void	(*t_test_fn)(void);
typedef void	(*t_ctx_fn)(void *);

extern sigjmp_buf g_test_stub_jmp;
extern const char *g_test_stub_last_error;
void		test_stub_begin_expect(void);
void		test_stub_end_expect(void);

static size_t	g_tests_passed;

static t_app	fresh_app(void)
{
    t_app	app;

    memset(&app, 0, sizeof(t_app));
    return (app);
}

static void	run_test(const char *name, t_test_fn fn)
{
    printf("→ %s\n", name);
    fn();
    puts("  ✓ ok");
    g_tests_passed++;
}

static void	expect_error(t_ctx_fn fn, void *ctx, const char *expected)
{
    int	status;

    status = sigsetjmp(g_test_stub_jmp, 1);
    if (status == 0)
    {
        test_stub_begin_expect();
        fn(ctx);
        test_stub_end_expect();
        assert(!"Expected error but function returned");
    }
    else
    {
        test_stub_end_expect();
        assert(g_test_stub_last_error != NULL);
        assert(strstr(g_test_stub_last_error, expected) != NULL);
    }
}

static void	test_is_line_empty(void)
{
    char with_content[] = " 1";
    char only_spaces[] = "   \n";
    char empty[] = "";

    assert(is_line_empty(only_spaces) == true);
    assert(is_line_empty(empty) == true);
    assert(is_line_empty(with_content) == false);
}

static void	test_strtrim_start(void)
{
    char leading_spaces[] = "\t  hello";
    char no_spaces[] = "world";

    assert(strcmp(strtrim_start(leading_spaces), "hello") == 0);
    assert(strcmp(strtrim_start(no_spaces), "world") == 0);
}

static void	test_array_len(void)
{
    char *array[] = {"north", "south", "east", NULL};

    assert(array_len(array) == 3);
    assert(array_len(NULL) == 0);
}

static void	test_get_rgba(void)
{
    uint32_t red = get_rgba(0xFF, 0x00, 0x00);
    uint32_t mixed = get_rgba(0x12, 0x34, 0x56);

    assert(red == 0xFF0000FF);
    assert(mixed == 0x123456FF);
}

static void	test_is_valid_char(void)
{
    assert(is_valid_char('1') == true);
    assert(is_valid_char('0') == true);
    assert(is_valid_char('N') == true);
    assert(is_valid_char(' ') == true);
    assert(is_valid_char('Z') == false);
}

static void	test_is_player_char(void)
{
    assert(is_player_char('N') == true);
    assert(is_player_char('S') == true);
    assert(is_player_char('X') == false);
}

static void	test_set_player_pos(void)
{
    t_app	app;
    char	row0[] = "111";
    char	row1[] = "1N1";
    char	row2[] = "111";
    char	*grid[] = {row0, row1, row2};

    memset(&app, 0, sizeof(t_app));
    set_player_pos(&app, grid, 1, 1);

    assert(fabs(app.player.pos_x - 1.5) < 1e-9);
    assert(fabs(app.player.pos_y - 1.5) < 1e-9);
    assert(app.direction == 'N');
    assert(grid[1][1] == '0');
}

static void	test_strtrim_end_nl(void)
{
    char	line[] = " 1010  \n";
    char	*trimmed;

    trimmed = strtrim_end_nl(line);
    assert(trimmed != NULL);
    assert(strcmp(trimmed, " 1010") == 0);
    free(trimmed);
    assert(strtrim_end_nl(NULL) == NULL);
}

static void	test_get_max_width(void)
{
    char *grid[] = {"1", "1234", "12", NULL};

    assert(get_max_width(grid) == 4);
}

static void	test_is_map_started(void)
{
    char *grid1[] = {NULL};
    char *grid2[] = {"1", NULL};

    assert(is_map_started(NULL) == false);
    assert(is_map_started(grid1) == false);
    assert(is_map_started(grid2) == true);
}

static void	test_realloc_grid(void)
{
    t_app	app;
    char	**grid;
    char	**expanded;

    app = fresh_app();
    grid = ft_calloc(2 + 1, sizeof(char *));
    assert(grid != NULL);
    grid[0] = ft_strdup("##");
    assert(grid[0] != NULL);

    expanded = realloc_grid(&app, grid, 4);
    assert(expanded != NULL);
    assert(strcmp(expanded[0], "##") == 0);
    assert(expanded[1] == NULL);
    assert(expanded[2] == NULL);
    assert(expanded[3] == NULL);
    free(expanded[0]);
    free(expanded);
}

static void	test_store_map(void)
{
    t_app	app;
    char	**grid;

    app = fresh_app();
    grid = ft_calloc(3 + 1, sizeof(char *));
    assert(grid != NULL);
    grid[0] = ft_strdup("1111");
    grid[1] = ft_strdup("1001");
    grid[2] = ft_strdup("111");
    assert(grid[0] && grid[1] && grid[2]);

    store_map(&app, grid, 3);
    assert(app.map == grid);
    assert(app.map_height == 3);
    assert(app.map_width == 4);

    free(grid[0]);
    free(grid[1]);
    free(grid[2]);
    free(grid);
    app.map = NULL;
}

static void	test_rgb_to_uint(void)
{
    t_app	app;
    uint32_t color;

    app = fresh_app();
    color = rgb_to_uint(&app, "12,34,56");
    assert(color == 0x0C2238FF);
}

typedef struct s_rgb_ctx
{
    t_app	*app;
    char	*rgb;
}t_rgb_ctx;

static void	run_rgb_to_uint(void *ctx)
{
    t_rgb_ctx	*data;

    data = ctx;
    rgb_to_uint(data->app, data->rgb);
}

static void	test_rgb_to_uint_invalid_format(void)
{
    t_app	app;
    t_rgb_ctx ctx;

    app = fresh_app();
    ctx.app = &app;
    ctx.rgb = "12,34";
    expect_error(run_rgb_to_uint, &ctx, "Invalid Color Format");
}

static void	test_rgb_to_uint_out_of_range(void)
{
    t_app	app;
    t_rgb_ctx ctx;

    app = fresh_app();
    ctx.app = &app;
    ctx.rgb = "256,0,0";
    expect_error(run_rgb_to_uint, &ctx, "not between");
}

typedef struct s_validate_color_ctx
{
    t_app	*app;
    char	*rgb;
    char	*trimmed;
}t_validate_color_ctx;

static void	run_validate_color(void *ctx)
{
    t_validate_color_ctx	*data;

    data = ctx;
    validate_color(data->app, data->rgb, data->trimmed);
}

static void	test_validate_color(void)
{
    t_app	app;
    bool	set_floor;
    bool	set_ceiling;
    char	trimmed_floor[] = "F";
    char	trimmed_ceiling[] = "C";

    app = fresh_app();
    set_floor = validate_color(&app, "220,100,0", trimmed_floor);
    set_ceiling = validate_color(&app, "50,60,70", trimmed_ceiling);
    assert(set_floor == true);
    assert(set_ceiling == true);
    assert(app.floor == 0xDC6400FF);
    assert(app.ceiling == 0x323C46FF);
}

static void	test_validate_color_duplicate(void)
{
    t_app	app;
    t_validate_color_ctx ctx;
    char	trimmed_floor[] = "F";
    char	*trimmed_dup;

    app = fresh_app();
    assert(validate_color(&app, "220,100,0", trimmed_floor) == true);
    trimmed_dup = ft_strdup("F");
    assert(trimmed_dup != NULL);
    ctx.app = &app;
    ctx.rgb = "1,2,3";
    ctx.trimmed = trimmed_dup;
    expect_error(run_validate_color, &ctx, "Color already defined");
}

typedef struct s_validate_texture_ctx
{
    t_app	*app;
    char	*path;
    char	*trimmed;
}t_validate_texture_ctx;

static void	run_validate_texture(void *ctx)
{
    t_validate_texture_ctx	*data;

    data = ctx;
    validate_texture(data->app, data->path, data->trimmed);
}

static void	test_validate_texture_success(void)
{
    t_app	app;
    char	template[] = "/tmp/c3d_texXXXXXX";
    char	trimmed[] = "NO";
    int	fd;

    app = fresh_app();
    fd = mkstemp(template);
    assert(fd != -1);
    close(fd);
    assert(validate_texture(&app, template, trimmed) == true);
    assert(app.tex.north_path != NULL);
    assert(strcmp(app.tex.north_path, template) == 0);
    free(app.tex.north_path);
    app.tex.north_path = NULL;
    unlink(template);
}

static void	test_validate_texture_duplicate(void)
{
    t_app	app;
    char	template[] = "/tmp/c3d_dupXXXXXX";
    char	trimmed[] = "NO";
    char	*trimmed_dup;
    char	*path_dup;
    t_validate_texture_ctx ctx;
    int	fd;

    app = fresh_app();
    fd = mkstemp(template);
    assert(fd != -1);
    close(fd);
    assert(validate_texture(&app, template, trimmed) == true);
    trimmed_dup = ft_strdup("NO");
    path_dup = ft_strdup(template);
    assert(trimmed_dup && path_dup);
    ctx.app = &app;
    ctx.path = path_dup;
    ctx.trimmed = trimmed_dup;
    expect_error(run_validate_texture, &ctx, "Identifier already defined");
    free(app.tex.north_path);
    app.tex.north_path = NULL;
    unlink(template);
}

static void	test_validate_texture_missing_path(void)
{
    t_app	app;
    t_validate_texture_ctx ctx;
    char	trimmed[] = "SO";

    app = fresh_app();
    ctx.app = &app;
    ctx.path = NULL;
    ctx.trimmed = trimmed;
    expect_error(run_validate_texture, &ctx, "Missing texture path");
}

static void	test_validate_texture_unreadable(void)
{
    t_app	app;
    t_validate_texture_ctx ctx;
    char	*trimmed_dup;
    char	*path_dup;

    app = fresh_app();
    trimmed_dup = ft_strdup("EA");
    path_dup = ft_strdup("/tmp/no_such_texture.cub");
    assert(trimmed_dup && path_dup);
    ctx.app = &app;
    ctx.path = path_dup;
    ctx.trimmed = trimmed_dup;
    expect_error(run_validate_texture, &ctx, "Unreadable texture");
}

int	main(void)
{
    run_test("is_line_empty handles blank and non-blank", test_is_line_empty);
    run_test("strtrim_start removes leading spaces", test_strtrim_start);
    run_test("array_len counts array entries", test_array_len);
    run_test("get_rgba packs RGB values", test_get_rgba);
    run_test("is_valid_char recognises map characters", test_is_valid_char);
    run_test("is_player_char detects player markers", test_is_player_char);
    run_test("set_player_pos centers player and clears tile", test_set_player_pos);
    run_test("strtrim_end_nl trims trailing whitespace", test_strtrim_end_nl);
    run_test("get_max_width finds widest row", test_get_max_width);
    run_test("is_map_started checks first row", test_is_map_started);
    run_test("realloc_grid grows grid without data loss", test_realloc_grid);
    run_test("store_map updates app metadata", test_store_map);
    run_test("rgb_to_uint converts decimal triplet", test_rgb_to_uint);
    run_test("rgb_to_uint rejects wrong format", test_rgb_to_uint_invalid_format);
    run_test("rgb_to_uint rejects out of range", test_rgb_to_uint_out_of_range);
    run_test("validate_color stores floor and ceiling colors", test_validate_color);
    run_test("validate_color detects duplicates", test_validate_color_duplicate);
    run_test("validate_texture stores path", test_validate_texture_success);
    run_test("validate_texture detects duplicates", test_validate_texture_duplicate);
    run_test("validate_texture requires path", test_validate_texture_missing_path);
    run_test("validate_texture rejects unreadable path", test_validate_texture_unreadable);
    printf("\n%zu unit tests passed.\n", g_tests_passed);
    return (0);
}
