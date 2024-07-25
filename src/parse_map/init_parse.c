
#include "../../includes/cub3D.h"


void init_parse(char *path)
{
    int fd;

    if(!namemap(path) == 4)
        return;
    if(open_file(path) == 0)
        return;
    
}

int open_file(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Error when try to open the file check permissions\n");
        return (0);
    }
    return (fd);
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
		printf("Invalid Format Map\n");
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
		printf("Invalid Format Map\n");
	return (j);
}
