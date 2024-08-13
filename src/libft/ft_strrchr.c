/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <diegmore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:29:14 by diegmore          #+#    #+#             */
/*   Updated: 2024/08/13 13:44:23 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_strrchr(const char *str, int c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
		i++;
	while (i >= j)
	{
		if (str[j] == (char)c)
			return (1);
		j++;
	}
	return (0);
}
