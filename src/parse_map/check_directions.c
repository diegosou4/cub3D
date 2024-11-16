/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:57:54 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 14:04:44 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	case_text(t_game *game, char *line, char **split)
{
	int	i;

	i = -1;
	void check_hole(t_game * game, int end) else if (line[0] == 'S'
			&& line[1] == 'O')
		i = 3;
	else if (line[0] == 'W' && line[1] == 'E')
		i = 6;
	else if (line[0] == 'E' && line[1] == 'A')
		i = 9;
	if (i != -1)
	{
		game->texture[i].texture.relative_path = ft_strdup(split[1]);
		game->texture[i + 1].texture.relative_path = ft_strdup(split[2]);
		game->texture[i + 2].texture.relative_path = ft_strdup(split[3]);
		game->texture[i].filled = true;
		game->texture[i + 1].filled = true;
		game->texture[i + 2].filled = true;
	}
}

void	case_addtex(t_game *game, char *line, char **split)
{
	int	i;

	i = -1;
	if (line[0] == 'D' && line[1] == 'R')
		i = 12;
	else if (line[0] == 'M' && line[1] == 'N')
		i = 13;
	else if (line[0] == 'O' && line[1] == 'B')
		i = 14;
	else if (line[0] == 'E' && line[1] == 'N')
		i = 15;
	if (i == -1)
		return ;
	game->texture[i].texture.relative_path = ft_strdup(split[1]);
	game->texture[i].filled = true;
}

void	case_color(t_game *game, char *line, char **split)
{
	char	**split2;

	split2 = ft_split(split[1], ',');
	if (len_darray(split2) != 3 || all_num(split2) == false)
	{
		ft_freedarray(split);
		ft_freedarray(split2);
		print_free(game, "Error when trying to parse the map");
	}
	if (line[0] == 'F')
	{
		game->color[F].r = ft_atoi(split2[0]);
		game->color[F].g = ft_atoi(split2[1]);
		game->color[F].b = ft_atoi(split2[2]);
		game->color[F].filled = true;
	}
	else if (line[0] == 'C')
	{
		game->color[C].r = ft_atoi(split2[0]);
		game->color[C].g = ft_atoi(split2[1]);
		game->color[C].b = ft_atoi(split2[2]);
		game->color[C].filled = true;
	}
	ft_freedarray(split2);
}

void	split_line(char *line, t_game *game, t_case_line_func l_func, int charl)
{
	char	**split;
	int		len;

	split = ft_split(line, ' ');
	len = len_darray(split);
	if (game->split_parse == true && len == 4)
	{
		if (ft_strlen(split[0]) == charl)
			l_func(game, line, split);
	}
	else if (len == 2 && game->split_parse == false)
	{
		if (ft_strlen(split[0]) == charl)
			l_func(game, line, split);
	}
	else if (ft_whitespaces(line) == false)
	{
		ft_freedarray(split);
		print_free(game, "Error when trying to parse the map");
	}
	ft_freedarray(split);
}

void	check_direction(t_game *game)
{
	int	i;

	i = 0;
	game->split_parse = true;
	while (game->map_info[i] != NULL && filled_textures(game) != true)
		split_line(game->map_info[i++], game, case_text, 2);
	game->split_parse = false;
	while (game->map_info[i] != NULL && filled_textures(game) != true)
		split_line(game->map_info[i++], game, case_addtex, 2);
	while (game->map_info[i] != NULL && filled_colors(game) != true)
		split_line(game->map_info[i++], game, case_color, 1);
	check_texture(game);
	while (game->map_info[i] != NULL
		&& ft_whitespaces(game->map_info[i]) == true)
		i++;
	if (i == ft_dstrlen(game->map_info))
		print_free(game, "Error when trying to parse the map");
	game->map = ft_dstrdup(game->map_info + i);
	check_map(game, i);
}
