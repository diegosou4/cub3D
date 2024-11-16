/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:49:17 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 13:49:45 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_freedarray(char **line)
{
	int	i;

	i = -1;
	if (line == NULL)
		return ;
	while (line[++i])
	{
		free(line[i]);
		line[i] = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}
