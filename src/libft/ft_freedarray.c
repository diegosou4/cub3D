
#include "../../includes/cub3D.h"

void	ft_freedarray(char **line)
{
	int	i;

	i = -1;
	if (line == NULL)
		return ;
	while (line[++i])
	{
		free(line[i]);
		line[i] = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}