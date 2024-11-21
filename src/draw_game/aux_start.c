/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:11:07 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/21 19:11:08 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3D.h"

void init_values3(t_game *game)
{
    int	i;

	i = -1;
    while (++i != NUM_TEXTURE - 1)
	{
		game->texture[i].filled = false;
		game->texture[i].duplicate = 0;
	}
    i = -1;
    while(++i != 2)
        game->color[i].duplicate = 0;

}