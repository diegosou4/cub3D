#include "../../includes/cub3D.h"

void clear_texture(t_game *game, int *status, t_img *texture)
{
    if(*status == 1)
    {
        mlx_destroy_image(game->mlx, texture->img);
        *status = 0;
    }
}

void free_walls(t_game *game)
{
    if(game->current_img == 0)
        return;
    while(game->current_img != -1)
    {
        mlx_destroy_image(game->mlx, game->wall[game->current_img].texture.img);
        game->current_img--;
    }

}  

void destroy_game(t_game *game)
{

    // Precisamos resolver esse problema
    mlx_clear_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->canva.img);
	mlx_destroy_window(game->mlx,game->win);
	mlx_destroy_display(game->mlx);
	free_game(game);
}