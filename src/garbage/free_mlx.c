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
	while(game->current_img != -1 && game->current_img <= 15)
	{
		mlx_destroy_image(game->mlx, game->texture[game->current_img].texture.img);
		game->current_img--;
	}

}  

