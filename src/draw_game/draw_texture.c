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

void init_enemies(t_game *game)
{
	int x, y;

	game->num_enemies = 0;
	for (y = 0; game->map[y] != NULL; y++)
	{
		for (x = 0; game->map[y][x] != '\0'; x++)
		{
			if (game->map[y][x] == '3' && game->num_enemies < MAX_ENEMIES)
			{
				game->enemies[game->num_enemies].x = x + 0.5; // Center in the cell
				game->enemies[game->num_enemies].y = y + 0.5; // Center in the cell
				game->num_enemies++;
			}
		}
	}
}

/* void draw_enemy(t_game *game)
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
	char *playCommand;
	static time_t last_played_time;
	time_t current_time;

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
				
				last_played_time = 0;
				current_time;
				playCommand = "paplay assets/music/BU.wav > /dev/null 2>&1 &";
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
				current_time = time(NULL);
				if (difftime(current_time, last_played_time) >= 10)
				{
					system(playCommand);
					last_played_time = current_time;
				}
			}
			stripe++;
		}
	}
	game->frameCtd++;
} */

void	draw_aux1(t_game *game)
{
	while (game->draw.y < game->draw.drawEndY)
    {
        game->draw.d = (game->draw.y) * 256 - HEIGHT * 128 + game->draw.spriteHeight * 128;
        game->draw.texY = ((game->draw.d * game->texture[15].texture.img_height) / game->draw.spriteHeight) / 256;
        game->draw.color = my_mlx_pixel_get(&game->texture[15].texture, game->draw.texX, game->draw.texY);
        if (game->draw.color != -16777216)
            my_mlx_pixel_put(&game->canva, game->draw.stripe, game->draw.y, game->draw.color);
        game->draw.y++;
    }
}

void	bu_timer(t_game *game)
{
	static time_t	last_played_time;
	time_t			current_time;

	current_time = time(NULL);
	if (difftime(current_time, last_played_time) >= 10)
    {
        system("paplay assets/music/BU.wav > /dev/null 2>&1 &");
        last_played_time = current_time;
    }
}

void	enemy_val_aux(t_game *game, int i)
{
	game->draw.enemyX = game->enemies[i].x - game->player.PosX;
	game->draw.enemyY = game->enemies[i].y - game->player.PosY;
	game->draw.invDet = 1.0 / (game->player.camera.PlaneX * game->player.dirY - game->player.dirX * game->player.camera.PlaneY);
	game->draw.transformX = game->draw.invDet * (game->player.dirY * game->draw.enemyX - game->player.dirX * game->draw.enemyY);
	game->draw.transformY = game->draw.invDet * (-game->player.camera.PlaneY * game->draw.enemyX + game->player.camera.PlaneX * game->draw.enemyY);
	game->draw.horizontal_offset = sin(game->frameCtd * game->draw.frequency) * game->draw.amplitude;
}

void	enemy_val_aux2(t_game *game)
{
	game->draw.spriteScreenX = (int)((WIDTH / 2) * (1 + game->draw.transformX / game->draw.transformY)) + (int)game->draw.horizontal_offset;
    game->draw.spriteHeight = abs((int)(HEIGHT / game->draw.transformY));
    game->draw.drawStartY = -game->draw.spriteHeight / 2 + HEIGHT / 2;
    if (game->draw.drawStartY < 0)
        game->draw.drawStartY = 0;
    game->draw.drawEndY = game->draw.spriteHeight / 2 + HEIGHT / 2;
    if (game->draw.drawEndY >= HEIGHT)
        game->draw.drawEndY = HEIGHT - 1;
    game->draw.spriteWidth = abs((int)(HEIGHT / game->draw.transformY));
    game->draw.drawStartX = -game->draw.spriteWidth / 2 + game->draw.spriteScreenX;
    if (game->draw.drawStartX < 0)
        game->draw.drawStartX = 0;
    game->draw.drawEndX = game->draw.spriteWidth / 2 + game->draw.spriteScreenX;
    if (game->draw.drawEndX >= WIDTH)
        game->draw.drawEndX = WIDTH - 1;
    game->draw.stripe = game->draw.drawStartX;
}

void draw_enemy(t_game *game)
{
	int	i;
    
	i = 0;
	game->draw.frequency = 0.02; 
	game->draw.amplitude = 10.0;
    while (i < game->num_enemies)
    {
		enemy_val_aux(game, i);
        if (game->draw.transformY > 0 && game->draw.transformY < game->player.ray.perpWallDist)
        {
           enemy_val_aux2(game);
            while (game->draw.stripe < game->draw.drawEndX)
            {
                game->draw.texX = (int)((game->draw.stripe - (-game->draw.spriteWidth / 2 + game->draw.spriteScreenX)) * game->texture[15].texture.img_width / game->draw.spriteWidth);
                if (game->draw.transformY > 0 && game->draw.stripe > 0 && game->draw.stripe < WIDTH && game->draw.transformY < game->player.ray.perpWallDist)
                {
                    game->draw.y = game->draw.drawStartY;
                    draw_aux1(game);
                }
                game->draw.stripe++;
            }
        }
		i++;
    }
	bu_timer(game);
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
