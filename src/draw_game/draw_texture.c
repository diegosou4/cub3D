
#include "../../includes/cub3D.h"




void draw_floor(t_game *game)
{
	int i;
	int j;
	i = 0;
	while(i < WIDTH)
	{
		j = 0;
		while(j < HEIGHT / 2)
		{
			my_mlx_pixel_put(&game->canva, i, j, SKY_COLOR);
			j++;
		}
		i++;
	}
	i = 0;
	while(i < WIDTH)
	{
		j = HEIGHT / 2;
		while(j < HEIGHT)
		{
			my_mlx_pixel_put(&game->canva, i, j, GRAY_COLOR);
			j++;
		}
		i++;
	}
}


void draw_map(t_game *game, int ftime)
{
	int i;
	int j;
	int x;
	int y;
	x = 0;
	y = 0;
	int size = 0;
	while(game->map[size] != NULL)
		size++;
	i = 0;
	while (i < size)
	{
		x = 0;
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			if(game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				if(ftime == 0)
				{
					define_direction(game,game->map[i][j]);
					game->player.PosX = j;
					game->player.PosY = i;
					game->player.Px = x + 8;
					game->player.Py = y + 8;
				}
			}	
			j++;
			x += TAM_X_P;
		}
		y += TAM_Y_P;
		i++;
	}
}
