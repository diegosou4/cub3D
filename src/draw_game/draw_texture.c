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
		color = (r << 16) | (g << 8) | b;
		my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentRayX, y, color);
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
int check_world(t_game *game, int pos)
{

	if (game->inside_wall && !game->changed_world) 
	{
    	game->changed_world = true;
    if (game->current_world == 1) 
	{
        game->current_world = 0;
        return (pos - game->current_world - game->light_on);
    } else if (game->current_world == 0) 
	{

        game->current_world = 1;
        return (pos - game->current_world - game->light_on);
    }
	} else if (!game->inside_wall && game->changed_world) 
	{
    	game->changed_world = false;
	}
	return (pos - game->current_world - game->light_on);
}

void draw_texture(t_game *game, double angle)
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
	if(pos != 12)
	{
		pos = check_world(game, pos);
	}
	rayx = (int)(wall_x * game->texture[pos].texture.img_width);
	if(game->player.ray.side == 0 && game->player.ray.rayDirX > 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	if(game->player.ray.side == 1 && game->player.ray.rayDirY < 0)
		rayx = game->texture[pos].texture.img_width - rayx - 1;
	if(game->current_world == 0)
		draw_walls_fade(game, &game->texture[pos].texture, rayx, 0);
	else
		draw_walls(game, &game->texture[pos].texture, rayx);
}
