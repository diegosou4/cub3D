/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:26:22 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 13:26:24 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_values2(t_game *game)
{
	game->n = 0;
	game->s = 0;
	game->e = 0;
	game->o = 0;
	game->rot_left = 0;
	game->rot_right = 0;
	game->framectd = 0;
	game->light_on = 0;
	game->current_img = -1;
	game->status_free = PARSE;
	game->x_mouse = WIDTH / 2;
	game->y_mouse = HEIGHT / 2;
	game->curr_map = 0;
	game->hit_door = false;
	game->hit_enemy = false;
	game->current_img = 0;
	game->inside_wall = false;
	game->changed_world = false;
	game->current_world = 0;
	game->sp = 1;
	init_values3(game);
}

void	init_values(t_game *game)
{
	game->player.camera.planex = 0;
	game->player.camera.planey = 0;
	game->player.deltax = 0;
	game->player.deltay = 0;
	game->player.dirx = 0;
	game->player.diry = 0;
	game->player.ray.ray_dir_x = 0;
	game->player.ray.ray_dir_y = 0;
	game->player.ray.side_distx = 0;
	game->player.ray.side_disty = 0;
	game->player.ray.delta_distx = 0;
	game->player.ray.delta_disty = 0;
	game->player.ray.perpwalldist = 0;
	game->player.ray.stepx = 0;
	game->player.ray.stepy = 0;
	game->player.ray.hit = 0;
	game->player.ray.side = 0;
	game->player.ray.lineheight = 0;
	game->player.ray.drawstart = 0;
	game->player.ray.drawend = 0;
	init_values2(game);
}

void	define_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.camera.planex = 0.66;
		game->player.diry = -1;
	}
	else if (direction == 'S')
	{
		game->player.camera.planex = -0.66;
		game->player.diry = 1;
	}
	else if (direction == 'W')
	{
		game->player.camera.planey = -0.66;
		game->player.dirx = -1;
	}
	else if (direction == 'E')
	{
		game->player.camera.planey = 0.66;
		game->player.dirx = 1;
	}
}

void	start_map2(t_game *game, int ftime, int i, int y)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (j < ft_strlen(game->map[i]))
	{
		if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
			|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
		{
			if (ftime == 0)
			{
				define_direction(game, game->map[i][j]);
				game->player.posx = j;
				game->player.posy = i;
				game->player.px = x + 8;
				game->player.py = y + 8;
			}
		}
		j++;
		x += TAM_X_P;
	}
}

void	start_map(t_game *game, int ftime)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (i < ft_dstrlen(game->map))
	{
		start_map2(game, ftime, i, y);
		y += TAM_Y_P;
		i++;
	}
}
