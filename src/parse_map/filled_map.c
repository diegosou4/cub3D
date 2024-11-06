
#include "../../includes/cub3D.h"


bool filled_textures(t_game *game)
{
    static int i;
    if(game->split_parse == true)
    {
        i = 0;
        while(i != 12)
        {
            if(game->texture[i].filled == false)
                return (false);
            i++;
        }
        return(true);
    }
    while(i != NUM_TEXTURE)
    {
        if(game->texture[i].filled == false)
            return (false);
        i++;
    }
    return(true);
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

    while(++i != NUM_TEXTURE) 
    {   
        if(check_ext(game->texture[i].texture.relative_path, ".xpm", "texture") != 4)
            print_free(game,"Invalid  Texture Path");
    }
   /*    if(check_ext(game->floor.texture.relative_path, ".xpm", "texture") != 4)
        print_free(game,"Invalid  Texture Path");
  if(check_ext(game->ceiling.texture.relative_path, ".xpm", "texture") != 4)
        print_free(game,"Invalid  Texture Path"); */
}