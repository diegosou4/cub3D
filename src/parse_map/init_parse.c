
#include "../../includes/cub3D.h"


// This ideia is salve the map in *map after this
// i will use slip to create **map
// and after i will check the map

void check_line(char *line, t_game *game)
{
	printf("line: %s\n", line);
	game->map = ft_split(line, '\n');
}


char *open_file(char *path)
{

	int fd;
	char *line;
	t_game *game;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (NULL);
	}
	line = open_read(fd);
	return(line);
}

void init_parse(char *path)
{
    int fd;
	t_game *game;
	char *line;	
    if(!namemap(path) == 4)
        return;
    line =	open_file(path);
	if(line == NULL)
		return;
	game = ft_calloc(sizeof(t_game) , 1);
	check_line(line,game);
    
}




char	*open_read(int fd)
{
	char	*buffer;
	int		sizestr;
	char	*str;

	sizestr = 1;
	str = NULL;
	while (sizestr != 0)
	{
		buffer = get_next_line(fd);
		sizestr = ft_strlen(buffer);
		if (sizestr == 0)
		{
			free(buffer);
			break ;
		}
		str = ftjoinmap(str, buffer);
	}
	return (str);
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
