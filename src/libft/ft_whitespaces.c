
#include "../../includes/cub3D.h"

bool ft_whitespaces(char *str)
{
    int i;

    if(str == NULL)
        return (false);
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
            return (false);
        i++;
    }
    return(true);
}

bool ft_whitespace(char c)
{
    if(c != ' ' && c != '\t' && c != '\n' && c != '\v' && c != '\f' && c != '\r')
            return (false);
    return(true);
}