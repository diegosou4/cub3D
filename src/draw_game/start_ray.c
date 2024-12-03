/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:15:11 by diegmore          #+#    #+#             */
/*   Updated: 2024/12/03 14:52:30 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	calculate_ray(t_game *game, int map_x, int map_y)
{
	if (game->player.ray.ray_dir_x < 0)
	{
		game->player.ray.stepx = -1;
		game->player.ray.side_distx = (game->player.posx - map_x)
			* game->player.deltax;
	}
	else
	{
		game->player.ray.stepx = 1;
		game->player.ray.side_distx = (map_x + 1.0 - game->player.posx)
			* game->player.deltax;
	}
	if (game->player.ray.ray_dir_y < 0)
	{
		game->player.ray.stepy = -1;
		game->player.ray.side_disty = (game->player.posy - map_y)
			* game->player.deltay;
	}
	else
	{
		game->player.ray.stepy = 1;
		game->player.ray.side_disty = (map_y + 1.0 - game->player.posy)
			* game->player.deltay;
	}
}

void	calculate_distance(t_game *game)
{
	if (game->player.ray.side == 0)
		game->player.ray.perpwalldist = (game->player.ray.side_distx
				- game->player.deltax);
	else
		game->player.ray.perpwalldist = (game->player.ray.side_disty
				- game->player.deltay);
	if (game->player.ray.perpwalldist < 0.000002)
		game->player.ray.perpwalldist += 0.000002;
}

void	hit_wall(t_game *game, int map_x, int map_y)
{
	while (game->map[map_y][map_x] != '1')
	{
		if (game->player.ray.side_distx < game->player.ray.side_disty)
		{
			game->player.ray.side_distx += game->player.deltax;
			map_x += game->player.ray.stepx;
			game->player.ray.side = 0;
		}
		else
		{
			game->player.ray.side_disty += game->player.deltay;
			map_y += game->player.ray.stepy;
			game->player.ray.side = 1;
		}
		if (check_door(game, map_x, map_y) == 1)
			break ;
	}
	calculate_distance(game);
}

void	check_rays(t_game *game)
{
	game->player.ray.lineheight = (int)(HEIGHT / game->player.ray.perpwalldist);
	game->player.ray.drawstart = -game->player.ray.lineheight / 2 + HEIGHT / 2;
	if (game->player.ray.drawstart < 0)
		game->player.ray.drawstart = 0;
	game->player.ray.drawend = game->player.ray.lineheight / 2 + HEIGHT / 2;
	if (game->player.ray.drawend >= HEIGHT || game->player.ray.drawend < 0)
		game->player.ray.drawend = HEIGHT - 1;
}

void	draw_ray(t_game *game, double angle)
{
	double	camera_x;
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;

	game->player.ray.currentrayx = angle;
	camera_x = 2 * angle / WIDTH - 1;
	ray_dir_x = game->player.dirx + game->player.camera.planex * camera_x;
	ray_dir_y = game->player.diry + game->player.camera.planey * camera_x;
	game->player.ray.ray_dir_x = ray_dir_x;
	game->player.ray.ray_dir_y = ray_dir_y;
	game->player.deltax = fabs(1 / ray_dir_x);
	game->player.deltay = fabs(1 / ray_dir_y);
	map_x = (int)game->player.posx;
	map_y = (int)game->player.posy;
	calculate_ray(game, map_x, map_y);
	hit_wall(game, map_x, map_y);
	check_rays(game);
	draw_texture(game, angle);
	draw_skyfloor(game, angle, game->player.ray.drawend, 1);
}
