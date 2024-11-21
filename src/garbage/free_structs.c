/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:42:03 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/21 17:43:44 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i != NUM_TEXTURE)
	{
		if (game->texture[i].texture.relative_path != NULL)
			free(game->texture[i].texture.relative_path);
		i++;
	}
}

void	free_map(t_game *game)
{
	if (game->map != NULL)
		ft_freedarray(game->map);
}

void	destroy_game(t_game *game)
{
	if (game->canva.img)
		mlx_destroy_image(game->mlx, game->canva.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	if (game->mlx != NULL)
		free(game->mlx);
	free_game(game);
	exit(0);
}

void	garabe_collector(t_game *game)
{
	free_map_info(game);
	free_ff_map(game);
	free_map(game);
	free_texture(game);
	free_walls(game);
	if (game->playcmd != NULL)
		free(game->playcmd);
	if (game->playbur != NULL)
		free(game->playbur);
	if (game->status_free != MLX)
		free_game(game);
	else if (game->status_free == MLX)
	{
		destroy_game(game);
	}
	exit(0);
}

void	print_free(t_game *game, char *errostr)
{
	garabe_collector(game);
	printf("%s\n", errostr);
	exit(0);
}
