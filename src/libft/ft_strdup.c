/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <diegmore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:19:52 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 13:52:52 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen((char *)src);
	dest = (char *)ft_calloc((size + 1), sizeof(char));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_dstrdup(char **src)
{
	char	**dest;
	int		i;

	i = 0;
	dest = (char **)ft_calloc((ft_dstrlen(src) + 1), sizeof(char *));
	while (src[i] != NULL)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
