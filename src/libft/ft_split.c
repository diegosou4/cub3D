/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <diegmore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:30:32 by diegmore          #+#    #+#             */
/*   Updated: 2024/07/31 11:34:20 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	ft_countwords(char *s, char sep)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i] != sep && s[i])
		{
			words++;
			i++;
		}
		while (s[i] != sep && s[i])
			i++;
	}
	return (words);
}

static int	ft_numberchar(char *s, char sep)
{
	int	i;
	int	numberchar;

	numberchar = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		while (s[i] != sep && s[i])
		{
			i++;
			numberchar++;
		}
		if (s[i] == sep)
			return (numberchar);
	}
	return (numberchar);
}

static int	ft_givestring(char *s, char sep, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		while (s[i] != sep && s[i])
		{
			dest[j] = s[i];
			i++;
			j++;
		}
		if (s[i] == sep)
			return (i);
	}
	return (i);
}

static void	*free_malloc(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		k;
	int		p;

	if (!s)
		return (0);
	p = 0;
	k = 0;
	i = 0;
	str = (char **)ft_calloc((ft_countwords((char *)s, c) + 1), sizeof(char *));
	if (!str)
		return (0);
	while (i < ft_countwords((char *)s, c))
	{
		str[i] = (char *)ft_calloc((ft_numberchar((char *)(s + p), c) + 1),
				sizeof(char));
		if (!str[i])
			return (free_malloc(str, i - 1));
		k = ft_givestring((char *)(s + p), c, str[i]);
		p = p + k;
		i++;
	}
	return (str);
}
