#include "../parsing.h"

bool	ft_is_empty_line(char *line)
{
	while (*line && *line != '\n')
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

char	*ft_strtrim_start(char *s)
{
	while (*s != '\0' && ft_isspace(*s))
		s++;
	return (s);
}

size_t	ft_array_len(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
