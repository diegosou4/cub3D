
#include "../../includes/cub3D.h"

bool ft_whitespaces(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
            return (false);
        i++;
    }
    return(true);
}