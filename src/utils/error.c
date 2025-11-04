#include "../parsing.h"

void	ft_error_exit(t_data *data, const char *msg)
{
	printf("Error : %s\n", msg);
	ft_free_data(data);
	exit(EXIT_FAILURE);
}
