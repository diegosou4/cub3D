/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <diegmore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:19:52 by diegmore          #+#    #+#             */
/*   Updated: 2024/08/13 10:56:03 by diegmore         ###   ########.fr       */
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

char **ft_dstrdup(char **src)
{
	char **dest;
	int i;

	i = 0;
	dest = (char **)ft_calloc((ft_dstrlen(src) + 1), sizeof(char *));
	printf("size %d\n",ft_dstrlen(src));
	while(src[i] != NULL)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	for(int j = 0; dest[j] != NULL; j++)
		printf("%s\n",dest[j]);
	return(dest);
}
// pega o src e faz uma copia
// usa o malloc para isso
// eu uso o calloc por ser mais seguro
// muito bom para uma string que tem
// um tamanho menor que o buff
