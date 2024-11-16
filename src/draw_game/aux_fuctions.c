/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fuctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:41:22 by dde-maga          #+#    #+#             */
/*   Updated: 2024/11/16 17:42:09 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	swift_rgb(t_game *game, int color, double fade_factor, int y)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * fade_factor);
	g = (int)(((color >> 8) & 0xFF) * fade_factor);
	b = (int)((color & 0xFF) * fade_factor);
	if (color != -16777216)
	{
		color = (r << 16) | (g << 8) | b;
		my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentrayx, y,
			color);
	}
}

void	bu_timer(t_game *game)
{
	static time_t	last_played_time;
	time_t			current_time;

	current_time = time(NULL);
	if (difftime(current_time, last_played_time) >= 10)
	{
		if (game->playbur != NULL)
			system(game->playbur);
		last_played_time = current_time;
	}
}

void	aux_rotate(t_game *game)
{
	game->rot_left = 0;
	game->rot_right = 0;
}

void	draw_enemy_stripes(t_game *game)
{
	while (game->draw.stripe < game->draw.drawendx)
	{
		game->draw.tex_x = (int)((game->draw.stripe - (-game->draw.spritewidth
						/ 2 + game->draw.spritescreenx))
				* game->texture[15].texture.img_width / game->draw.spritewidth);
		if (game->draw.transformy > 0 && game->draw.stripe > 0
			&& game->draw.stripe < WIDTH
			&& game->draw.transformy < game->player.ray.perpwalldist)
		{
			game->draw.y = game->draw.drawstarty;
			draw_aux1(game);
		}
		game->draw.stripe++;
	}
}
