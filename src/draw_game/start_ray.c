/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:15:11 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 13:15:14 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	calculate_ray(t_game *game, int map_x, int map_y)
{
	if (game->player.ray.ray_dir_x < 0)
	{
		game->player.ray.stepX = -1;
		game->player.ray.sideDistX = (game->player.PosX - map_x)
			* game->player.deltax;
	}
	else
	{
		game->player.ray.stepX = 1;
		game->player.ray.sideDistX = (map_x + 1.0 - game->player.PosX)
			* game->player.deltax;
	}
	if (game->player.ray.ray_dir_y < 0)
	{
		game->player.ray.stepY = -1;
		game->player.ray.sideDistY = (game->player.PosY - map_y)
			* game->player.deltay;
	}
	else
	{
		game->player.ray.stepY = 1;
		game->player.ray.sideDistY = (map_y + 1.0 - game->player.PosY)
			* game->player.deltay;
	}
}

void	calculate_distance(t_game *game)
{
	if (game->player.ray.side == 0)
		game->player.ray.perpWallDist = (game->player.ray.sideDistX
				- game->player.deltax);
	else
		game->player.ray.perpWallDist = (game->player.ray.sideDistY
				- game->player.deltay);
	if (game->player.ray.perpWallDist < 0.1)
		game->player.ray.perpWallDist = 0.1;
}

void	hit_wall(t_game *game, int map_x, int map_y)
{
	while (game->map[map_y][map_x] != '1')
	{
		if (game->player.ray.sideDistX < game->player.ray.sideDistY)
		{
			game->player.ray.sideDistX += game->player.deltax;
			map_x += game->player.ray.stepX;
			game->player.ray.side = 0;
		}
		else
		{
			game->player.ray.sideDistY += game->player.deltay;
			map_y += game->player.ray.stepY;
			game->player.ray.side = 1;
		}
		if (check_door(game, map_x, map_y) == 1)
			break ;
	}
	calculate_distance(game);
}

void	check_rays(t_game *game)
{
	game->player.ray.lineheight = (int)(HEIGHT / game->player.ray.perpWallDist);
	game->player.ray.drawStart = -game->player.ray.lineheight / 2 + HEIGHT / 2;
	if (game->player.ray.drawStart < 0)
		game->player.ray.drawStart = 0;
	game->player.ray.drawEnd = game->player.ray.lineheight / 2 + HEIGHT / 2;
	if (game->player.ray.drawEnd >= HEIGHT || game->player.ray.drawEnd < 0)
		game->player.ray.drawEnd = HEIGHT - 1;
}

void	draw_ray(t_game *game, double angle)
{
	double	camera_x;
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;

	game->player.ray.currentRayX = angle;
	camera_x = 2 * angle / WIDTH - 1;
	ray_dir_x = game->player.dirX + game->player.camera.PlaneX * camera_x;
	ray_dir_y = game->player.dirY + game->player.camera.PlaneY * camera_x;
	game->player.ray.ray_dir_x = ray_dir_x;
	game->player.ray.ray_dir_y = ray_dir_y;
	game->player.deltax = fabs(1 / ray_dir_x);
	game->player.deltay = fabs(1 / ray_dir_y);
	map_x = (int)game->player.PosX;
	map_y = (int)game->player.PosY;
	calculate_ray(game, map_x, map_y);
	hit_wall(game, map_x, map_y);
	check_rays(game);
	draw_texture(game, angle);
	draw_skyfloor(game, angle, game->player.ray.drawEnd, 1);
}
