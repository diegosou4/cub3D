
#include "../../includes/cub3D.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void init_parse(char *path)
{
    
    if(!namemap(path) == 4)
        return;
        
}


int	namemap(char *pathname)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_strlen(pathname);
	if (i <= 4)
	{
		printf("Formato de mapa invalido\n");
		return (0);
	}
	if (pathname[i - 1] == 'b')
		j = 1;
	if (pathname[i - 2] == 'u')
		j += 1;
	if (pathname[i - 3] == 'c')
		j += 1;
	if (pathname[i - 4] == '.')
		j += 1;
	if (j == 0)
		printf("Formato de mapa invalido\n");
	return (j);
}
