/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:34:36 by dde-maga          #+#    #+#             */
/*   Updated: 2024/11/16 17:35:08 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_flashlight(t_game *game)
{
	double	frequency;
	double	amplitude;
	double	vertical_offset;
	int		x;
	int		y;

	frequency = 0.05;
	amplitude = 10.0;
	vertical_offset = sin(game->framectd * frequency) * amplitude;
	y = 0;
	while (y < game->texture[14].texture.img_height && game->light_on)
	{
		x = 0;
		while (x < game->texture[14].texture.img_width)
		{
			my_mlx_pixel_put(&game->canva, WIDTH / 2 + x, (HEIGHT / 2 + 150
					+ (int)vertical_offset) + y,
				my_mlx_pixel_get(&game->texture[14].texture, x, y));
			x++;
		}
		y++;
	}
	game->framectd++;
}

int	cc_mmap(t_game *game, int map_x, int map_y, int color)
{
	color = RBG_BLACK;
	if (game->map[map_y][map_x] == '1')
		color = RBG_WHITE;
	else if (game->map[map_y][map_x] == 'S' || game->map[map_y][map_x] == 'N' ||
				game->map[map_y][map_x] == 'E'
					|| game->map[map_y][map_x] == 'O')
		color = RBG_YELLOW;
	return (color);
}

void	draw_minimap_background(t_game *game, int map_height,
		double start_map_x, double start_map_y)
{
	int	color;
	int	y;
	int	x;
	int	map_x;
	int	map_y;

	color = -16777216;
	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_SIZE)
		{
			map_x = (int)(start_map_x + x / (MINIMAP_SCALE * TILE_SIZE));
			map_y = (int)(start_map_y + y / (MINIMAP_SCALE * TILE_SIZE));
			if (map_x >= 0 && map_y >= 0 && map_y < map_height)
			{
				if (map_x < ft_strlen(game->map[map_y]))
					my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y
						+ MINIMAP_MARGIN, cc_mmap(game, map_x, map_y,
							color));
			}
		}
	}
}

void	draw_minimap(t_game *game)
{
	int		map_height;
	int		minimap_radius;
	double	start_map_x;
	double	start_map_y;

	map_height = 0;
	while (game->map[map_height] != NULL)
		map_height++;
	minimap_radius = MINIMAP_SIZE / 2;
	start_map_x = game->player.posx - minimap_radius / (MINIMAP_SCALE
			* TILE_SIZE);
	start_map_y = game->player.posy - minimap_radius / (MINIMAP_SCALE
			* TILE_SIZE);
	draw_minimap_background(game, map_height, start_map_x, start_map_y);
	paintimage(game, &game->texture[13], minimap_radius + TILE_SIZE,
		minimap_radius + TILE_SIZE);
}
