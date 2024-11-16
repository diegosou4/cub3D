/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_fuctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:33:11 by dde-maga          #+#    #+#             */
/*   Updated: 2024/11/16 17:33:32 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	key_rot(t_game *game, int keycode)
{
	if (keycode == L_AR)
		game->rot_left = 1;
	else if (keycode == R_AR)
		game->rot_right = 1;
}

void	key_ligths(t_game *game, int keycode)
{
	if (keycode == KEY_F)
	{
		if (game->light_on == 0)
			game->light_on = 1;
		else
			game->light_on = 0;
	}
}

void	key_direction(t_game *game, int keycode)
{
	if (keycode == KEY_A)
	{
		game->x_mov -= 1;
		game->o = 1;
	}
	else if (keycode == KEY_D)
	{
		game->x_mov += 1;
		game->e = 1;
	}
	else if (keycode == KEY_W)
	{
		game->y_mov -= 1;
		game->n = 1;
	}
	else if (keycode == KEY_S)
	{
		game->y_mov += 1;
		game->s = 1;
	}
}

void	define_mov(t_game *game, int keycode)
{
	key_rot(game, keycode);
	key_ligths(game, keycode);
	key_direction(game, keycode);
}

// Resolver essa funcao
int	key_drop(int keycode, t_game *game)
{
	if (keycode == KEY_W && (game->y_mov == 0 || game->y_mov == -1))
	{
		game->y_mov += 1;
		game->n = 0;
	}
	else if (keycode == KEY_S && (game->y_mov == 0 || game->y_mov == 1))
	{
		game->y_mov -= 1;
		game->s = 0;
	}
	else if (keycode == KEY_A && (game->x_mov == 0 || game->x_mov == -1))
	{
		game->x_mov += 1;
		game->o = 0;
	}
	else if (keycode == KEY_D && (game->x_mov == 0 || game->x_mov == 1))
	{
		game->x_mov -= 1;
		game->e = 0;
	}
	else if ((game->rot_left == 1 && keycode == L_AR) || (game->rot_right == 1
			&& keycode == R_AR))
		aux_rotate(game);
	return (0);
}
