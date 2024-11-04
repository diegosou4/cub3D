
#include "../../includes/cub3D.h"


bool filled_textures(t_game *game)
{
    int i;
    i = 0;
    while(i != 12)
    {
        if(game->wall[i].filled == false)
            return (false);
        i++;
    }

    return (true);
}

bool filled_colors(t_game *game)
{
    int i;

    i = 0;
    while(i != 2)
    {
        if(game->color[i].filled == false)
            return (false);
        i++;
    }
    return (true);
}



void check_texture(t_game *game)
{
   int i;

   i = -1;

    while(++i != 12) 
    {
        if(check_ext(game->wall[i].texture.relative_path, ".xpm", "texture") != 4)
            print_free(game,"Invalid  Texture Path");
    }
   /*    if(check_ext(game->floor.texture.relative_path, ".xpm", "texture") != 4)
        print_free(game,"Invalid  Texture Path");
  if(check_ext(game->ceiling.texture.relative_path, ".xpm", "texture") != 4)
        print_free(game,"Invalid  Texture Path"); */
}