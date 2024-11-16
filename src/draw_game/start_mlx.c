/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:03:59 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 13:17:04 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	cal_shadow(t_game *game)
{
	if (game->light_on == 0
		&& game->player.ray.perpWallDist >= MAX_RENDER_DISTANCE)
		game->player.ray.perpWallDist = MAX_RENDER_DISTANCE;
	else if (game->player.ray.perpWallDist >= MAX_RENDER_DISTANCE * 3)
		game->player.ray.perpWallDist = MAX_RENDER_DISTANCE * 3;
}

int	check_door(t_game *game, int map_x, int map_y)
{
	if (game->map[map_y][map_x] == '1')
	{
		game->hit_door = false;
		return (1);
	}
	else if (game->map[map_y][map_x] == '2')
	{
		game->hit_door = true;
		return (1);
	}
	return (0);
}

void	draw_allray(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		draw_ray(game, x);
		x++;
	}
	if (game->light_on == 0)
		;
	draw_minimap(game);
	draw_flashlight(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
}
