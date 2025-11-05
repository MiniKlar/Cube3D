#include "../parsing.h"

void	error_exit(t_data *data, const char *msg)
{
	printf("Error : %s\n", msg);
	free_data(data);
	exit(EXIT_FAILURE);
}
