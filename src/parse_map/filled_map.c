
#include "../../includes/cub3D.h"


bool filled_textures(t_game *game)
{
    int i;

    i = 0;
    while(i != 4)
    {
        if(game->wall[i].filled == false)
            return (false);
        i++;
    }
    return (true);
}