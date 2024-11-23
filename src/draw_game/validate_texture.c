/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:29:19 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 17:34:06 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	hex_color(t_game *game, int pos)
{
	int	color;

	color = game->color[pos].r << 16 | game->color[pos].g << 8 | \
			game->color[pos].b;
	return (color);
}

void	draw_sky(t_game *game, double angle, double x, int pos)
{
	if (pos == 1)
	{
		if (x < HEIGHT)
		{
			while (x < HEIGHT)
			{
				my_mlx_pixel_put(&game->canva, angle, x, hex_color(game, pos));
				x++;
			}
		}
	}
}

void	draw_skyfloor(t_game *game, double angle, double x, int pos)
{
	int	y;

	y = 0;
	if (game->map[(int)game->player.posy][(int)game->player.posx] == '2')
		return ;
	if (pos == 0)
	{
		if (x > 0)
		{
			while (y < x)
			{
				my_mlx_pixel_put(&game->canva, angle, y, hex_color(game, pos));
				y++;
			}
		}
		return ;
	}
	draw_sky(game, angle, x, pos);
}

t_img	load_img(t_game *game, char *path)
{
	t_img	img;

	img.relative_path = path;
	img.img = mlx_xpm_file_to_image(game->mlx, img.relative_path,
			&img.img_width, &img.img_height);
	if (img.img == NULL)
	{
		printf("Texture path: %s\n", path);
		printf("Error\nInvalid texture path\n");
		garabe_collector(game);
	}
	img.status = 1;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	return (img);
}

void	load_wall(t_game *game)
{
	int	i;
	int	img_height;
	int	img_width;

	i = 0;
	while (i != NUM_TEXTURE)
	{
		game->texture[i].texture = load_img(game,
				game->texture[i].texture.relative_path);
		img_height = game->texture[i].texture.img_width;
		img_width = game->texture[i].texture.img_height;
		if (img_height > img_width)
			print_free(game, "Invalid Texture Dimensions");
		game->current_img = i;
		i++;
	}
	if (game->texture[14].texture.img_height > 200)
		print_free(game, "Invalid Texture Dimensions");
}
