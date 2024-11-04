#include "../../includes/cub3D.h"

void draw_walls_fade(t_game *game, t_img *texture, double angle, int pos)
{
	double step;
	double texPos;
	double fade_factor;
	int texY;
	int color;
	int y;
	int r;
	int g;
	int b;

	step = 1.0 * texture->img_height / game->player.ray.lineheight;
	texPos = (game->player.ray.drawStart - HEIGHT / 2 + game->player.ray.lineheight / 2) * step;
	y = game->player.ray.drawStart;
	if (game->light_on == 0)
		fade_factor = 1.0 - (game->player.ray.perpWallDist / MAX_RENDER_DISTANCE);
	else
		fade_factor = 1.0 - (game->player.ray.perpWallDist / (MAX_RENDER_DISTANCE * 3));
	if (fade_factor < 0) fade_factor = 0.0; // Clamp fade factor
	while (y < game->player.ray.drawEnd)
	{
		texY = (int)texPos & (texture->img_height - 1);
		texPos += step;
		color = my_mlx_pixel_get(texture, game->wall[pos].texture.img_height - (int)angle, texY);
		r = (int)(((color >> 16) & 0xFF) * fade_factor);
		g = (int)(((color >> 8) & 0xFF) * fade_factor);
		b = (int)((color & 0xFF) * fade_factor);
		color = (r << 16) | (g << 8) | b;
		my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentRayX, y, color);
		y++;
	}
}

void draw_walls(t_game *game, t_img *texture, double angle, int pos)
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
		color = my_mlx_pixel_get(texture, game->wall[pos].texture.img_height - (int)angle, texY);
		my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentRayX, y, color);
		y++;
  }
}

int return_pos(t_game *game)
{
	//ROBOT VERSION
	/* if(game->player.ray.side == 1 && game->player.ray.rayDirY > 0)
		return 3;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX < 0)
		return 9;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		return 6;
	else if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		return 0; */
	//+++++++++++++++++++++
	//Liminal Version
	if(game->player.ray.side == 1 && game->player.ray.rayDirY > 0 && game->light_on == 0)
		return 1;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX < 0 && game->light_on == 0)
		return 4;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0 && game->light_on == 0)
		return 7;
	else if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0 && game->light_on == 0)
		return 10;
	else if(game->player.ray.side == 1 && game->player.ray.rayDirY > 0 && game->light_on == 1)
		return 2;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX < 0 && game->light_on == 1)
		return 5;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0 && game->light_on == 1)
		return 8;
	else if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0 && game->light_on == 1)
		return 11;
	return 0;
}


void draw_texture(t_game *game, double angle)
{
	double wall_x;
	double rayx;
	int pos;

	draw_skyfloor1(game,angle,game->player.ray.drawEnd,0);
	//draw_skyfloor(game,angle,game->player.ray.drawEnd,0);
	if(game->player.ray.side == 0)
		wall_x = game->player.PosY + game->player.ray.perpWallDist * game->player.ray.rayDirY;
	else
		wall_x = game->player.PosX + game->player.ray.perpWallDist * game->player.ray.rayDirX;
	wall_x -= floor(wall_x);
	pos = return_pos(game);
	rayx = (int)(wall_x * game->wall[pos].texture.img_width);
	if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		rayx = game->wall[pos].texture.img_width - rayx - 1;
	if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		rayx = game->wall[pos].texture.img_width - rayx - 1;
	draw_walls_fade(game, &game->wall[pos].texture, rayx,pos);
}
