

#include "../../includes/cub3D.h"

/* void draw_floor(t_game *game)
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
} */

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

void draw_minimap(t_game *game)
{
  int i;
  i = 0;


  while(game->map[i] != NULL)
  {
    int j = 0;
    while(game->map[i][j] != '\0')
    {
      if(game->map[i][j] == '1')
        draw(j * 10, i * 10, RBG_BLUE, game);
      else if(game->map[i][j] == '0')
        draw(j * 10, i * 10, RBG_WHITE, game);
        
      j++;
    }
    i++;
  }
    //test_player(game, RBG_RED);
}