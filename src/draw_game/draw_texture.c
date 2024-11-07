#include "../../includes/cub3D.h"


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
		color = my_mlx_pixel_get(texture, texture->img_height - (int)angle, texY);
		my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentRayX, y, color);
		y++;
  }
}

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
	if (fade_factor < 0) fade_factor = 0.0;
	while (y < game->player.ray.drawEnd)
	{
		texY = (int)texPos & (texture->img_height - 1);
		texPos += step;
		color = my_mlx_pixel_get(texture, texture->img_height - (int)angle, texY);
		r = (int)(((color >> 16) & 0xFF) * fade_factor);
		g = (int)(((color >> 8) & 0xFF) * fade_factor);
		b = (int)((color & 0xFF) * fade_factor);
		if (color != -16777216)
		{
			color = (r << 16) | (g << 8) | b;
			my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentRayX, y, color);
		}
		y++;
	}
}



int return_pos(t_game *game)
{
	if(game->hit_door == true)
		return 12;
	if(game->player.ray.side == 1 && game->player.ray.rayDirY > 0)
		return 1 + game->light_on;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX < 0)
		return 4 + game->light_on;
	else if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		return 7 + game->light_on;
	else if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		return 10 + game->light_on;
	return 0;
}


/* void draw_texture(t_game *game, double angle)
{
	double wall_x;
	double rayx;
	int pos;

	draw_skyfloor(game,angle,game->player.ray.drawEnd,0);
	if(game->player.ray.side == 0)
		wall_x = game->player.PosY + game->player.ray.perpWallDist * game->player.ray.rayDirY;
	else
		wall_x = game->player.PosX + game->player.ray.perpWallDist * game->player.ray.rayDirX;
	wall_x -= floor(wall_x);
	pos = return_pos(game);
	rayx = (int)(wall_x * game->texture[pos].texture.img_width);
	if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	draw_walls_fade(game, &game->texture[pos].texture, rayx, 0);
} */

void draw_enemy(t_game *game)
{
	double enemyX;
	double enemyY;
	double invDet;
	double transformX;
	double transformY;
	double frequency; 
	double amplitude;
	double horizontal_offset;
	int spriteScreenX;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
	int stripe;
	int texX;
	int y;
	int d;
	int texY;
	int color;

	enemyX = game->enemy_x - game->player.PosX;
	enemyY = game->enemy_y - game->player.PosY;
	invDet = 1.0 / (game->player.camera.PlaneX * game->player.dirY - game->player.dirX * game->player.camera.PlaneY);
	transformX = invDet * (game->player.dirY * enemyX - game->player.dirX * enemyY);
	transformY = invDet * (-game->player.camera.PlaneY * enemyX + game->player.camera.PlaneX * enemyY);
	frequency = 0.02;
	amplitude = 10.0;
	horizontal_offset = sin(game->frameCtd * frequency) * amplitude;
	if (transformY > 0 && transformY < game->player.ray.perpWallDist) 
	{
		spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY)) + (int)horizontal_offset;
		spriteHeight = abs((int)(HEIGHT / transformY));
		drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if (drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		spriteWidth = abs((int)(HEIGHT / transformY));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX;
		while (stripe < drawEndX)
		{
			texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX)) * game->texture[15].texture.img_width / spriteWidth);
			if (transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < game->player.ray.perpWallDist)
			{
				y = drawStartY;
				while (y < drawEndY)
				{
					d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128;
					texY = ((d * game->texture[15].texture.img_height) / spriteHeight) / 256;
					color = my_mlx_pixel_get(&game->texture[15].texture, texX, texY);
					if (color != -16777216)
						my_mlx_pixel_put(&game->canva, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
	}
	game->frameCtd++;
}




void draw_texture(t_game *game, double angle)
{
	double	wall_x;
	double	rayx;
	int		pos;

	draw_skyfloor(game, angle, game->player.ray.drawEnd, 0);
	if (game->player.ray.side == 0)
		wall_x = game->player.PosY + game->player.ray.perpWallDist * game->player.ray.rayDirY;
	else
		wall_x = game->player.PosX + game->player.ray.perpWallDist * game->player.ray.rayDirX;
	wall_x -= floor(wall_x);
	pos = return_pos(game);
	rayx = (int)(wall_x * game->texture[pos].texture.img_width);
	if (game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	if (game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	draw_walls_fade(game, &game->texture[pos].texture, rayx, pos);
}
