
#include "../../includes/cub3D.h"


// This ideia is salve the map in *map after this
// i will use slip to create **map
// and after i will check the map


void check_line(char *line, t_game *game)
{
	// printf("line: %s\n", line);
	game->map = ft_split(line, '\n');
	int j = 0;

	// I need solve the problem because the 
	// map is not being saved correctly
	// split dont save when the line is empty
	// I need to fix this
	// I did try to fix this in the function ft_split
	// but it`s not best solution
	while(game->map[j] != NULL)
    {
        printf("Map[%d]: %s\n", j, game->map[j]);
        j++;
    }
	
	free(line);
	check_direction(game);
	
}


char *open_file(char *path)
{

	int fd;
	char *line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (NULL);
	}
	line = open_read(fd);
	return(line);
}

void fill_game(t_game *game)
{
	int i;

	i = 0;

	while(i != 4)
	{
		game->wall[i].filled = false;
		game->wall[i].texture.img_width = 64;
        game->wall[i].texture.img_height = 64;
		i++;
	}
}

void init_parse(char *path)
{
    int fd;
	t_game *game;
	char *line;	
    if(!check_ext(path,".cub","map") == 4)
        return;
    line =	open_file(path);
	if(line == NULL)
		return;
	game = ft_calloc(sizeof(t_game) , 1);
	fill_game(game);
	
	check_line(line,game);
	garabe_collector(game);
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

int	check_ext(char *pathname, char *format, char *type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_strlen(pathname);
	if (i <= 4)
	{
		printf("Invalid Format %s\n", type);
		return (0);
	}
	if (pathname[i - 1] == format[3])
		j = 1;
	if (pathname[i - 2] == format[2])
		j += 1;
	if (pathname[i - 3] == format[1])
		j += 1;
	if (pathname[i - 4] == format[0])
		j += 1;
	if (j == 0)
		printf("Invalid Format %s\n", type);
	return (j);
}
