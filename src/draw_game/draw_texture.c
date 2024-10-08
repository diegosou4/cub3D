
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

void draw_walls(t_game *game, t_img *texture, double angle)
{
  double step;
  double texPos;
  int texY;
  int color;
  int y;

  step = 1.0 * texture->img_height / game->player.ray.lineheight;
  texPos = (game->player.ray.drawStart - HEIGHT / 2 + game->player.ray.lineheight / 2) * step;
  y = game->player.ray.drawStart;
  while(y < game->player.ray.drawEnd)
  {
    texY = (int)texPos & (texture->img_height - 1);
    texPos += step;
    color = my_mlx_pixel_get(texture, (int)angle, texY);
    my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentRayX, y, color);
    y++;
  }

}

// O Wall_x e a posicao exata da parede que foi atingida
// 

void draw_texture(t_game *game, double angle)
{

	double wall_x;
  double rayx;

	if(game->player.ray.side == 0)
		wall_x = game->player.PosY + game->player.ray.perpWallDist * game->player.ray.rayDirY;
	else
		wall_x = game->player.PosX + game->player.ray.perpWallDist * game->player.ray.rayDirX;

	wall_x -= floor(wall_x);
  rayx = (int)(wall_x * 64);;
  
  if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
    rayx = 64 - rayx - 1;
  if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
    rayx = 64 - rayx - 1;
  if(game->player.ray.side == 1 && game->player.ray.rayDirY > 0)
    draw_walls(game, &game->wall[SOUTH].texture, rayx);
  if(game->player.ray.side == 0 && game->player.ray.rayDirX < 0)
    draw_walls(game, &game->wall[EAST].texture, rayx);
  if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
    draw_walls(game, &game->wall[WEST].texture, rayx);
  if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
    draw_walls(game, &game->wall[NORTH].texture, rayx);
}