/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:10:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/21 20:33:12 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_line(t_game *game)
{
	game->map_info = ft_split(game->line, '\n');
	free(game->line);
	game->player.px = -1;
	game->player.py = -1;
	game->player.direction = -1;
	check_direction(game);
}

char	*open_file(char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (NULL);
	}
	line = open_read(fd);
	return (line);
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

void	init_parse(char *path)
{
	t_game	*game;

	if (!(check_ext(path, ".cub", "map") == 4))
		return ;
	game = ft_calloc(sizeof(t_game), 1);
	init_values(game);
	game->line = open_file(path);
	if (game->line == NULL)
	{
		printf("Error\n");
		free(game);
		return ;
	}
	check_line(game);
	if (game->player.direction == -1)
		print_free(game, "Error Parse");
	start_window(game);
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
		if (sizestr == 1 && buffer[0] == '\n')
		{
			free(buffer);
			buffer = ft_strdup(" \n");
		}
		str = ftjoinmap(str, buffer);
	}
	return (str);
}
