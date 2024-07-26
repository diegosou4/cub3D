
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