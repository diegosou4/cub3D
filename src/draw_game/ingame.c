/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ingame.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:07:21 by diegmore          #+#    #+#             */
/*   Updated: 2024/12/04 19:54:08 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_event(int keycode, t_game *game)
{
	mouse_monitor(game, keycode);
	if (keycode == ESC)
	{
		system("pkill paplay > /dev/null 2>&1");
		game->status_free = MLX;
		garabe_collector(game);
	}
	return (0);
}

void	start_window(t_game *game)
{
	game->status_free = MLX;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->canva.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->canva.addr = mlx_get_data_addr(game->canva.img,
			&game->canva.bits_per_pixel,
			&game->canva.line_length,
			&game->canva.endian);
	load_wall(game);
	game->status_free = MLX;
	ingame(game);
}

void	save_msc(t_game *game)
{
	game->playcmd = ft_strdup("paplay assets/music/li.wav > /dev/null 2>&1 &");
	game->playbur = ft_strdup("paplay assets/music/BU.wav > /dev/null 2>&1 &");
}

void	ingame(t_game *game)
{
	start_map(game, 0);
	init_enemies(game);
	draw_allray(game);
	save_msc(game);
	if (game->playcmd != NULL)
	{
		system(game->playcmd);
	}
	mlx_hook(game->win, 2, (1L << 0), key_event, game);
	mlx_hook(game->win, 17, (1L << 0), garabe_collector, game);
	mlx_hook(game->win, 3, (1L << 1), key_drop, game);
	mlx_hook(game->win, 6, (1L << 6), mouse_track, game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop_hook(game->mlx, mouse_monitor, game);
	mlx_loop(game->mlx);
}
