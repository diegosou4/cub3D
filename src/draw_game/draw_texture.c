#include "../../includes/cub3D.h"


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
    if(game->player.ray.side == 1 && game->player.ray.rayDirY > 0)
        return 3;
    else if(game->player.ray.side == 0 && game->player.ray.rayDirX < 0)
        return 9;
    else if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
        return 6;
    else if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
        return 0;
    return 0;
}

void draw_texture(t_game *game, double angle)
{
	double wall_x;
	double rayx;
  int pos;

  draw_skyfloor(game,angle,game->player.ray.drawEnd,0);
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
	fade_factor = 1.0 - (game->player.ray.perpWallDist / MAX_RENDER_DISTANCE);
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

// O Wall_x e a posicao exata da parede que foi atingida
// 
/*void draw_texture(t_game *game, double angle)
{
	double	wall_x;
	double	rayx;
	int		pos;

	if (game->player.ray.side == 0)
		wall_x = game->player.PosY + game->player.ray.perpWallDist * game->player.ray.rayDirY;
	else
		wall_x = game->player.PosX + game->player.ray.perpWallDist * game->player.ray.rayDirX;
	wall_x -= floor(wall_x);
	if (game->player.ray.side == 1 && game->player.ray.rayDirY > 0)
		pos = SOUTH;
	else if (game->player.ray.side == 0 && game->player.ray.rayDirX < 0)
		pos = EAST;
	else if (game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		pos = WEST;
	else if (game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		pos = NORTH;
	rayx = (int)(wall_x * game->wall[pos].texture.img_width);
	if (game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		rayx = game->wall[pos].texture.img_width - rayx - 1;
	if (game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		rayx = game->wall[pos].texture.img_width - rayx - 1;
	draw_walls(game, &game->wall[pos].texture, rayx, pos);
}*/


/* void draw_texture(t_game *game, double angle)
{

	double wall_x;
	double rayx;
	int pos;
	

	if(game->player.ray.side == 0)
		wall_x = game->player.PosY + game->player.ray.perpWallDist * game->player.ray.rayDirY;
	else
		wall_x = game->player.PosX + game->player.ray.perpWallDist * game->player.ray.rayDirX;
	wall_x -= floor(wall_x);

    pos = return_pos(game);
    rayx = (int)(wall_x * game->wall[pos].texture.img_width);

	if(game->player.ray.side == 1 && game->player.ray.rayDirY > 0)
		pos = SOUTH;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX < 0)
		pos = EAST;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		pos = WEST;
	else if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		pos = NORTH;
	rayx = (int)(wall_x * game->wall[pos].texture.img_width);

	if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		rayx = game->wall[pos].texture.img_width - rayx - 1;
	if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		rayx = game->wall[pos].texture.img_width - rayx - 1;
	draw_walls(game, &game->wall[pos].texture, rayx,pos);
} */

/* void draw_walls_with_fade(t_game *game, t_img *texture, int rayx, int pos, double fade_factor, double angle)
{
	for (int y = game->player.ray.drawStart; y < game->player.ray.drawEnd; y++)
	{
		// Get the color from the texture at the given ray position
		int color = my_mlx_pixel_get(texture, rayx, (y * texture->img_height) / game->player.ray.lineheight);

		// Apply fade factor to each color component (R, G, B)
		int r = (int)((color >> 16 & 0xFF) * fade_factor);
		int g = (int)((color >> 8 & 0xFF) * fade_factor);
		int b = (int)((color & 0xFF) * fade_factor);

		color = (r << 16) | (g << 8) | b; // Reconstruct color with fade

		// Put the pixel with adjusted color on the screen
		my_mlx_pixel_put(&game->canva, angle, y, color);
	}
} */