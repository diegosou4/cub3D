#include "../../includes/cub3D.h"


int ft_dstrlen(char **str)
{
    int i;

    i = 0;
    while(str[i] != NULL)
        i++;
    return(i);
}