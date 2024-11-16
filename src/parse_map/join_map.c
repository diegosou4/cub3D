/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:12:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/16 14:12:58 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ftjoinmap2(char *str, char *buffer, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str)
	{
		new_str[i] = str[i];
		i++;
	}
	while (buffer[j] && buffer)
	{
		new_str[i + j] = buffer[j];
		j++;
	}
	new_str[i + j] = '\0';
}

char	*ftjoinmap(char *str, char *buffer)
{
	char	*new_str;
	int		len_s;
	int		len_b;

	len_s = ft_strlen(str);
	len_b = ft_strlen(buffer);
	if (!str)
	{
		new_str = (char *)malloc(sizeof(char) * (len_b + 1));
		joinmap(new_str, buffer);
		return (new_str);
	}
	new_str = (char *)malloc(sizeof(char) * (len_s + len_b + 1));
	if (new_str == NULL)
	{
		free(buffer);
		free(str);
		return (NULL);
	}
	ftjoinmap2(str, buffer, new_str);
	free(buffer);
	free(str);
	return (new_str);
}

char	*joinmap(char *new_str, char *buffer)
{
	int	j;

	j = 0;
	while (buffer[j] != '\0')
	{
		new_str[j] = buffer[j];
		j++;
	}
	new_str[j] = '\0';
	free(buffer);
	return (new_str);
}

int	valid_line(char *line)
{
	int	i;

	i = 2;
	if (line[i] == ' ')
	{
		i++;
		while (line[i] != '\0')
		{
			if (line[i] == ' ')
				return (0);
			i++;
		}
	}
	return (1);
}

bool	all_num(char **split2)
{
	int	i;
	int	num;
	int	j;

	i = 0;
	num = 0;
	while (i != 3)
	{
		j = 0;
		if (ft_strlen(split2[i]) == 0 || ft_strlen(split2[i]) > 3)
			return (false);
		while (split2[i][j] != '\0')
		{
			num = ft_atoi(split2[i]);
			if (ft_isdigit(split2[i][j]) == 0 || num < 0 || num > 255)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
