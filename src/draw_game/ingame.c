/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ingame.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:07:21 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 12:16:22 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	save_msc(t_game *game)
{
	game->playCmd = ft_strdup("paplay assets/music/li.wav > /dev/null 2>&1 &");
	game->playBur = ft_strdup("paplay assets/music/BU.wav > /dev/null 2>&1 &");
}

void	ingame(t_game *game)
{
	start_map(game, 0);
	init_enemies(game);
	draw_allray(game);
	save_msc(game);
	if (game->playCmd != NULL)
	{
		system(game->playCmd);
	}
	mlx_hook(game->win, 2, (1L << 0), key_event, game);
	mlx_hook(game->win, 3, (1L << 1), key_drop, game);
	mlx_hook(game->win, 6, (1L << 6), mouse_track, game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop_hook(game->mlx, mouse_monitor, game);
	mlx_loop(game->mlx);
}
