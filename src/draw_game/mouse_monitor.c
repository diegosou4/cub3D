/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:02 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 12:39:01 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	mouse_track(int x, int y, t_game *game)
{
	if (game->x_mouse == x && game->y_mouse == y)
		return (0);
	game->x_mouse = x;
	game->y_mouse = y;
	return (0);
}

int	mouse_monitor(t_game *game, int keycode)
{
	static int	prev_x_mouse;
	double		deltax;

	prev_x_mouse = WIDTH / 2;
	deltax = game->x_mouse - prev_x_mouse;
	if ((game->x_mouse > 0 && game->x_mouse < WIDTH) || keycode == R_AR
		|| keycode == L_AR || keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
	{
		deltax = game->x_mouse - prev_x_mouse;
		if (deltax != 0 || keycode == R_AR || keycode == L_AR)
		{
			if (deltax > 0 || game->rot_right == 1)
				arrow_right(game);
			else if (deltax < 0 || game->rot_left == 1)
				arrow_left(game);
			prev_x_mouse = WIDTH / 2;
		}
		player_mov(game);
		draw_allray(game);
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	}
	return (1);
}

int	arrow_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(-ROT_SPEED) - game->player.diry
		* sin(-ROT_SPEED);
	game->player.diry = old_dir_x * sin(-ROT_SPEED) + game->player.diry
		* cos(-ROT_SPEED);
	old_plane_x = game->player.camera.planex;
	game->player.camera.planex = game->player.camera.planex * cos(-ROT_SPEED)
		- game->player.camera.planey * sin(-ROT_SPEED);
	game->player.camera.planey = old_plane_x * sin(-ROT_SPEED)
		+ game->player.camera.planey * cos(-ROT_SPEED);
	return (1);
}

int	arrow_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(ROT_SPEED) - game->player.diry
		* sin(ROT_SPEED);
	game->player.diry = old_dir_x * sin(ROT_SPEED) + game->player.diry
		* cos(ROT_SPEED);
	old_plane_x = game->player.camera.planex;
	game->player.camera.planex = game->player.camera.planex * cos(ROT_SPEED)
		- game->player.camera.planey * sin(ROT_SPEED);
	game->player.camera.planey = old_plane_x * sin(ROT_SPEED)
		+ game->player.camera.planey * cos(ROT_SPEED);
	return (1);
}
