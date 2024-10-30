

#include "../../includes/cub3D.h"

void draw(int x,int y, int color, t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
 return;	
	i++;
	while(i < 6)
	{
		j = 0;
		while(j < 6)
		{
			my_mlx_pixel_put(&game->canva, x + i, y + j, color);
			j++;
		}
		i++;
	}
}