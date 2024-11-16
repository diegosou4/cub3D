/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:41:01 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 13:44:40 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	clear_texture(t_game *game, int *status, t_img *texture)
{
	if (*status == 1)
	{
		mlx_destroy_image(game->mlx, texture->img);
		*status = 0;
	}
}

void	free_walls(t_game *game)
{
	if (game->current_img == 0)
		return ;
	while (game->current_img != -1 && game->current_img <= 15)
	{
		mlx_destroy_image(game->mlx,
			game->texture[game->current_img].texture.img);
		game->current_img--;
	}
}

void	free_ff_map(t_game *game)
{
	if (game->ff_map != NULL)
		ft_freedarray(game->ff_map);
}

void	free_map_info(t_game *game)
{
	if (game->map_info != NULL)
		ft_freedarray(game->map_info);
}

void	free_game(t_game *game)
{
	if (game != NULL)
		free(game);
}
