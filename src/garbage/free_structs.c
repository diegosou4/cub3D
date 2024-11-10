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
    while(i != NUM_TEXTURE)
    {
        if(game->texture[i].texture.relative_path != NULL)
            free(game->texture[i].texture.relative_path);
        i++;
    }
}
void free_map(t_game *game)
{
  if(game->map != NULL)
    ft_freedarray(game->map);
}

void destroy_game(t_game *game)
{
    if (game->canva.img)
        mlx_destroy_image(game->mlx, game->canva.img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free_game(game);
    exit(0);
}
void garabe_collector(t_game *game)
{
    
    free_map_info(game);
    free_ff_map(game);
    free_map(game);
    free_texture(game);
    free_walls(game);
    if(game->status_free != MLX)
        free_game(game);
    else if(game->status_free == MLX)
        destroy_game(game);
    exit(0);
}

void print_free(t_game *game, char *errostr)
{
    garabe_collector(game);
    printf("%s\n",errostr);
    exit(0);
}