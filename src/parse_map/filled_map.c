/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filled_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:06:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/21 20:13:20 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	filled_textures(t_game *game)
{
	static int	i;

	if (game->split_parse == true)
	{
		i = 0;
		while (i != 12)
		{
			if (game->texture[i].duplicate == 1)
				print_free(game, "Invalid Duplicate Texture");
			if (game->texture[i].filled == false)
				return (false);
			i++;
		}
		return (true);
	}
	while (i != NUM_TEXTURE)
	{
		if (game->texture[i].duplicate == 1)
			print_free(game, "Invalid Duplicate Texture");
		if (game->texture[i].filled == false)
			return (false);
		i++;
	}
	return (true);
}

bool	filled_colors(t_game *game)
{
	int	i;

	i = 0;
	while (i != 2)
	{
		if (game->color[i].filled == false)
			return (false);
		i++;
	}
	return (true);
}

void	check_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i != NUM_TEXTURE)
	{
		if (check_ext(game->texture[i].texture.relative_path, ".xpm",
				"texture") != 4)
			print_free(game, "Invalid  Texture Path");
		if (game->texture[i].duplicate == 1)
			print_free(game, "Duplicate Texture");
		i++;
	}
	i = 0;
	while (i != 2)
	{
		if (game->color[i].duplicate == 1)
			print_free(game, "Duplicate Color");
		i++;
	}
}

int	count_x(t_game *game)
{
	int	row;
	int	col;
	int	x;

	x = 0;
	row = 0;
	col = 0;
	while (game->ff_map[col] != NULL)
	{
		while (game->ff_map[col][row] != '\0')
		{
			if (game->ff_map[col][row] == 'x')
				x++;
			row++;
		}
		row = 0;
		col++;
	}
	return (x);
}

void	check_map(t_game *game, int start)
{
	int	end;

	(void)start;
	game->status_free = FINAL;
	end = sizemap(game);
	check_fl(game, 0, end);
	check_hole(game, end);
	check_middle(game, end);
	if (count_x(game) == 1)
		print_free(game, "Invalid Map");
}
