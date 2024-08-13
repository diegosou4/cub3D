#include "../../includes/cub3D.h"

void free_map_info(t_game *game)
{
    if(game->map_info != NULL)
        ft_freedarray(game->map_info);
}

void free_game(t_game *game)
{
    if(game != NULL)
        free(game);
}

void free_texture(t_game *game)
{
    int i;

    i = 0;
    while(i != 4)
    {
        if(game->wall[i].texture.relative_path != NULL)
        free(game->wall[i].texture.relative_path);
        i++;
    }
}
void free_map(t_game *game)
{
  if(game->map != NULL)
    ft_freedarray(game->map);
}
void garabe_collector(t_game *game, int option)
{
    if(option == PARSE)
        free_map_info(game);
    else if(option == FINAL)
        free_map(game);
    free_texture(game);
    free_game(game);
}

void print_free(t_game *game, char *errostr, int option)
{
    garabe_collector(game, option);
    printf("%s\n",errostr);
    exit(0);
}