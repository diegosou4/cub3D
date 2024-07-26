/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <diegmore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:19:52 by diegmore          #+#    #+#             */
/*   Updated: 2024/07/26 15:10:05 by diegmore         ###   ########.fr       */
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

// pega o src e faz uma copia
// usa o malloc para isso
// eu uso o calloc por ser mais seguro
// muito bom para uma string que tem
// um tamanho menor que o buff
