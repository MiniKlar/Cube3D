#include "header.h"

void ft_error_exit(const char *msg)
{
	printf("Error :\n%s", msg);
	exit(EXIT_FAILURE);
}

bool cub_extension(char *file)
{
	int len;

	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (ft_strncmp(file + (len - 4), ".cub", 4) == 0)
		return (1);
	return (0);
}

int readable_map(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error : ");
		exit(EXIT_FAILURE);
	}
	return(fd);
}

bool parsing(int ac, char **av)
{
	int fd;
	(void)ac;
	if (!cub_extension(av[1]))
		ft_error_exit("File must end with <.cub>\n");
	fd = readable_map(av[1]);
	return (printf("End of Parsing\n"), 0);
}
