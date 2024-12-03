/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:03:59 by diegmore          #+#    #+#             */
/*   Updated: 2024/12/03 15:16:08 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	cal_shadow(t_game *game)
{
	if (game->light_on == 0
		&& game->player.ray.perpwalldist >= MAX_RENDER_DISTANCE)
		game->player.ray.perpwalldist = MAX_RENDER_DISTANCE;
	else if (game->player.ray.perpwalldist >= MAX_RENDER_DISTANCE * 3)
		game->player.ray.perpwalldist = MAX_RENDER_DISTANCE * 3;
}

int	check_door(t_game *game, int map_x, int map_y)
{
	if (game->map[map_y][map_x] == '1')
	{
		game->hit_door = false;
		return (1);
	}
	else if (game->map[map_y][map_x] == '2' && game->light_on == 0)
	{
		game->hit_door = true;
		return (1);
	}
	else if (game->map[map_y][map_x] == '2' && game->light_on == 1)
	{
		game->hit_door = false;
		return (0);
	}
	return (0);
}

void	draw_loading_screen(t_game *game)
{
	int	x;
	int	color;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = my_mlx_pixel_get(&game->texture[12].texture, x
					* game->texture[12].texture.img_width / WIDTH, y
					* game->texture[12].texture.img_height / HEIGHT);
			my_mlx_pixel_put(&game->canva, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_allray(t_game *game)
{
	int	x;
	int	playertilex;
	int	playertiley;

	x = 0;
	playertilex = (int)game->player.posx;
	playertiley = (int)game->player.posy;
	while (x < WIDTH)
	{
		draw_ray(game, x);
		x++;
	}
	if (game->map[playertiley][playertilex] == '2')
		draw_loading_screen(game);
	else
	{
		if (game->light_on == 0 && game->current_world == 0)
			draw_enemy(game);
		draw_minimap(game);
		draw_flashlight(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
}
