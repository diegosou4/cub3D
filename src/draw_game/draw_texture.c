/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:47:38 by diegmore          #+#    #+#             */
/*   Updated: 2024/12/03 15:11:38 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_walls(t_game *game, t_img *texture, double angle)
{
	double	step;
	double	texpos;
	int		texy;
	int		color;
	int		y;

	step = 1.0 * texture->img_height / game->player.ray.lineheight;
	texpos = (game->player.ray.drawstart - HEIGHT / 2
			+ game->player.ray.lineheight / 2) * step;
	y = game->player.ray.drawstart;
	while (y < game->player.ray.drawend)
	{
		texy = (int)texpos & (texture->img_height - 1);
		texpos += step;
		color = my_mlx_pixel_get(texture, texture->img_height - (int)angle,
				texy);
		my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentrayx, y,
			color);
		y++;
	}
}

void	draw_walls_fade(t_game *game, t_img *texture, double angle)
{
	double	texpos;
	int		texy;
	int		color;
	int		y;

	game->player.step = 1.0 * texture->img_height / game->player.ray.lineheight;
	texpos = (game->player.ray.drawstart - HEIGHT / 2
			+ game->player.ray.lineheight / 2) * game->player.step;
	y = game->player.ray.drawstart;
	if (game->light_on == 0)
		game->player.fade_factor = 1.0 - (game->player.ray.perpwalldist
				/ MAX_RENDER_DISTANCE);
	else
		game->player.fade_factor = 1.0 - (game->player.ray.perpwalldist
				/ (MAX_RENDER_DISTANCE * 3));
	if (game->player.fade_factor < 0)
		game->player.fade_factor = 0.0;
	while (y < game->player.ray.drawend)
	{
		texy = (int)texpos & (texture->img_height - 1);
		texpos += game->player.step;
		color = my_mlx_pixel_get(texture, texture->img_height - (int)angle,
				texy);
		swift_rgb(game, color, game->player.fade_factor, y++);
	}
}

int	return_pos(t_game *game)
{
	int	texture_loc;

	texture_loc = 0;
	if (game->hit_door == true)
		return (12);
	if (game->player.ray.side == 1 && game->player.ray.ray_dir_y > 0)
		texture_loc = 1 + game->light_on;
	else if (game->player.ray.side == 0 && game->player.ray.ray_dir_x < 0)
		texture_loc = 4 + game->light_on;
	else if (game->player.ray.side == 0 && game->player.ray.ray_dir_x > 0)
		texture_loc = 7 + game->light_on;
	else if (game->player.ray.side == 1 && game->player.ray.ray_dir_y < 0)
		texture_loc = 10 + game->light_on;
	texture_loc = check_world(game, texture_loc);
	if (game->current_world == 1)
		texture_loc -= game->light_on;
	return (texture_loc);
}

int	check_world(t_game *game, int pos)
{
	if (game->inside_wall && !game->changed_world && game->light_on == 1)
	{
		game->changed_world = true;
		if (game->current_world == 1)
			return (pos - (game->current_world = 0));
		else if (game->current_world == 0)
			return (pos - (game->current_world = 1));
	}
	else if (!game->inside_wall && game->changed_world)
	{
		game->changed_world = false;
	}
	return (pos - game->current_world);
}

void	draw_texture(t_game *game, double angle)
{
	double		wall_x;
	double		rayx;
	int			pos;
	t_draw_func	draw_func[2];

	draw_func[0] = draw_walls_fade;
	draw_func[1] = draw_walls;
	if (game->map[(int)game->player.posy][(int)game->player.posx] != '2')
		draw_skyfloor(game, angle, game->player.ray.drawend, 0);
	if (game->player.ray.side == 0)
		wall_x = game->player.posy + game->player.ray.perpwalldist
			* game->player.ray.ray_dir_y;
	else
		wall_x = game->player.posx + game->player.ray.perpwalldist
			* game->player.ray.ray_dir_x;
	wall_x -= floor(wall_x);
	pos = return_pos(game);
	rayx = (int)(wall_x * game->texture[pos].texture.img_width);
	if (game->player.ray.side == 0 && game->player.ray.ray_dir_x > 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	if (game->player.ray.side == 1 && game->player.ray.ray_dir_y < 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	if (game->map[(int)game->player.posy][(int)game->player.posx] != '2')
		draw_func[game->current_world](game, &game->texture[pos].texture, rayx);
}

/* void hit_door(t_game *game, double angle)
{
	double		wall_x;
	double		rayx;
	if (game->player.ray.side == 0)
		wall_x = game->player.posy + game->player.door.perpwalldist
			* game->player.ray.ray_dir_y;
	else
		wall_x = game->player.posx + game->player.door.perpwalldist
			* game->player.ray.ray_dir_x;
	wall_x -= floor(wall_x);
	if (game->player.ray.side == 0 && game->player.ray.ray_dir_x > 0)
		rayx = game->texture[12].texture.img_width - rayx - 1;
	if (game->player.ray.side == 1 && game->player.ray.ray_dir_y < 0)
		rayx = game->texture[12].texture.img_width - rayx - 1;
	draw_walls(game, 12,angle);
} */