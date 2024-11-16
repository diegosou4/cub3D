#include "../../includes/cub3D.h"


void init_enemies(t_game *game)
{
	int x;
    int y;

    y = 0;
	game->num_enemies = 0;
	while (game->map[y] != NULL)
	{
        x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] == '3' && game->num_enemies < MAX_ENEMIES)
			{
				game->enemies[game->num_enemies].x = x + 0.5;
				game->enemies[game->num_enemies].y = y + 0.5;
				game->num_enemies++;
			}
            x++;
		}
        y++;
	}
}


void	draw_aux1(t_game *game)
{
	while (game->draw.y < game->draw.drawEndY)
    {
        game->draw.d = (game->draw.y) * 256 - HEIGHT * 128 + game->draw.spriteHeight * 128;
        game->draw.texY = ((game->draw.d * game->texture[15].texture.img_height) / game->draw.spriteHeight) / 256;
        game->draw.color = my_mlx_pixel_get(&game->texture[15].texture, game->draw.texX, game->draw.texY);
        my_mlx_pixel_put(&game->canva, game->draw.stripe, game->draw.y, game->draw.color);
        game->draw.y++;
    }
}

void	enemy_val_aux(t_game *game, int i)
{
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
	int     i;
	double  distance;
    
	i = -1;
	game->draw.frequency = 0.02; 
	game->draw.amplitude = 10.0;
    while (++i < game->num_enemies)
    {
		game->draw.enemyX = game->enemies[i].x - game->player.PosX;
		game->draw.enemyY = game->enemies[i].y - game->player.PosY;
		distance = sqrt(game->draw.enemyX * game->draw.enemyX + game->draw.enemyY * game->draw.enemyY);
		if (distance < MIN_PROXIMITY_DISTANCE)
            continue;
		enemy_val_aux(game, i);
        if (game->draw.transformY > 0 && game->draw.transformY < game->player.ray.perpWallDist)
        {
			bu_timer(game);
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
    }
    game->frameCtd++;
}