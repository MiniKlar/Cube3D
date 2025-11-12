#include "cube.h"
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

sigjmp_buf	g_test_stub_jmp;
bool		g_test_stub_should_jump = false;
const char	*g_test_stub_last_error = NULL;

void	free_app(t_app *app)
{
	(void)app;
}

void	test_stub_begin_expect(void)
{
	g_test_stub_last_error = NULL;
	g_test_stub_should_jump = true;
}

void	test_stub_end_expect(void)
{
	g_test_stub_should_jump = false;
}

static void	handle_error(const char *label, const char *msg)
{
	g_test_stub_last_error = msg;
	if (g_test_stub_should_jump)
		siglongjmp(g_test_stub_jmp, 1);
	fprintf(stderr, "[TEST STUB] %s triggered: %s\n", label, msg);
	abort();
}

void	error_exit_1(t_app *app, char *msg, char **tab)
{
	(void)app;
	(void)tab;
	handle_error("error_exit_1", msg);
}

void	error_exit_2(t_app *app, char *msg, char **tab, char *tab_2)
{
	(void)app;
	(void)tab;
	(void)tab_2;
	handle_error("error_exit_2", msg);
}

void	error_exit(t_app *app, char *msg, int fd)
{
	(void)app;
	(void)fd;
	handle_error("error_exit", msg);
}
