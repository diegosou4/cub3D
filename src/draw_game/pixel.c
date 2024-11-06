/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:31:29 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/01 19:32:34 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	paintimage(t_game *game, t_texture *img, int sx, int sy)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->texture.img_height)
	{
		x = 0;
		while (x < img->texture.img_width)
		{
			my_mlx_pixel_put(&game->canva, sx + x, sy + y, my_mlx_pixel_get(&img->texture,
					x, y));
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (color == -16777216)
	{
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
