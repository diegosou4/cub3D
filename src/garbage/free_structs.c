#include "../../includes/cub3D.h"

void free_ff_map(t_game *game)
{
    if(game->ff_map != NULL)
        ft_freedarray(game->ff_map);
}

void free_map_info(t_game *game)
{
    if(game->map_info != NULL)
        ft_freedarray(game->map_info);
    free_ff_map(game);
}
void free_flood_map(t_game *game)
{
    if(game->ff_map != NULL)
        ft_freedarray(game->ff_map);
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
/*     if(game->ceiling.texture.relative_path != NULL)
        free(game->ceiling.texture.relative_path);
    if(game->floor.texture.relative_path != NULL)
        free(game->floor.texture.relative_path); */
}
void free_map(t_game *game)
{
  if(game->map != NULL)
    ft_freedarray(game->map);
}
void garabe_collector(t_game *game)
{
    if(game->status_free == PARSE)
        free_map_info(game);
    else if(game->status_free == FLOOD)
    {
          free_map(game);
          free_flood_map(game);
    }
    else if(game->status_free == FINAL)
    {
        free_ff_map(game);
        free_map(game);
    }
    printf("Chego aqui");
    // free_texture(game);
    free_walls(game,4);
    free_game(game);
}

void print_free(t_game *game, char *errostr)
{
    garabe_collector(game);
    printf("%s\n",errostr);
    exit(0);
}