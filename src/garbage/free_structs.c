#include "../../includes/cub3D.h"

void free_map(t_game *game)
{
    if(game->map != NULL)
        ft_freedarray(game->map);
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

void garabe_collector(t_game *game)
{
    free_map(game);
    free_texture(game);
    free_game(game);
}

void print_free(t_game *game, char *errostr)
{
    garabe_collector(game);
    printf("%s\n",errostr);
    exit(0);
}