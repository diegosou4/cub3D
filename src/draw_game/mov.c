/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:40:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 12:44:02 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_w(t_game *game)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = game->player.posx + game->player.dirx * MOVE_SPEED;
	newpos_y = game->player.posy + game->player.diry * MOVE_SPEED;
	if (game->map[(int)game->player.posy][(int)newpos_x] != '1')
	{
		game->player.posx = newpos_x;
	}
	if (game->map[(int)newpos_y][(int)game->player.posx] != '1')
	{
		game->player.posy = newpos_y;
	}
	if (game->map[(int)newpos_y][(int)newpos_x] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
	return (0);
}

int	key_s(t_game *game)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = game->player.posx - game->player.dirx * MOVE_SPEED;
	newpos_y = game->player.posy - game->player.diry * MOVE_SPEED;
	if (game->map[(int)game->player.posy][(int)newpos_x] != '1')
	{
		game->player.posx = newpos_x;
	}
	if (game->map[(int)newpos_y][(int)game->player.posx] != '1')
	{
		game->player.posy = newpos_y;
	}
	if (game->map[(int)newpos_y][(int)newpos_x] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
	return (0);
}

int	key_d(t_game *game)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = game->player.posx + game->player.camera.planex * MOVE_SPEED;
	newpos_y = game->player.posy + game->player.camera.planey * MOVE_SPEED;
	if (game->map[(int)game->player.posy][(int)newpos_x] != '1')
	{
		game->player.posx = newpos_x;
	}
	if (game->map[(int)newpos_y][(int)game->player.posx] != '1')
	{
		game->player.posy = newpos_y;
	}
	if (game->map[(int)newpos_y][(int)newpos_x] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
	return (0);
}

int	key_a(t_game *game)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = game->player.posx - game->player.camera.planex * MOVE_SPEED;
	newpos_y = game->player.posy - game->player.camera.planey * MOVE_SPEED;
	if (game->map[(int)game->player.posy][(int)newpos_x] != '1')
	{
		game->player.posx = newpos_x;
	}
	if (game->map[(int)newpos_y][(int)game->player.posx] != '1')
	{
		game->player.posy = newpos_y;
	}
	if (game->map[(int)newpos_y][(int)newpos_x] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
	return (0);
}

int	player_mov(t_game *game)
{
	if (game->n && game->y_mov == -1)
		key_w(game);
	if (game->s && game->y_mov == 1)
		key_s(game);
	if (game->e && game->x_mov == 1)
		key_d(game);
	if (game->o && game->x_mov == -1)
		key_a(game);
	if (game->rot_left == 1)
		arrow_left(game);
	if (game->rot_right == 1)
		arrow_right(game);
	return (0);
}
