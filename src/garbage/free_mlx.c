#include "../../includes/cub3D.h"


void free_walls(t_game *game, int texture)
{
    while(texture >= 0 && texture < 4)
    {
        if(game->wall[texture].texture.relative_path != NULL)
        {
            mlx_destroy_image(game->mlx, game->wall[texture].texture.img);
            free(game->wall[texture].texture.relative_path);
        }
            
        texture--;
    }
}

void destroy_game(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->canva.img);
	mlx_destroy_window(game->mlx,game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}