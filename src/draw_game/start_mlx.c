



#include "../../includes/cub3D.h"

void calculate_ray(t_game *game, int mapX, int mapY)
{
	if(game->player.ray.rayDirX < 0)
	{
		game->player.ray.stepX = -1;
		game->player.ray.sideDistX = (game->player.PosX - mapX) * game->player.deltax;
	}
	else
	{
		game->player.ray.stepX = 1;
		game->player.ray.sideDistX = (mapX + 1.0 - game->player.PosX) * game->player.deltax;
	}
	if(game->player.ray.rayDirY < 0)
	{
		game->player.ray.stepY = -1;
		game->player.ray.sideDistY = (game->player.PosY - mapY) * game->player.deltay;
	}
	else
	{
		game->player.ray.stepY = 1;
		game->player.ray.sideDistY = (mapY + 1.0 - game->player.PosY) * game->player.deltay;
	}
}
void calculate_distance(t_game *game)
{
	game->player.ray.perpWallDist = 0;

	if(game->player.ray.side == 0)
		game->player.ray.perpWallDist = (game->player.ray.sideDistX - game->player.deltax);
	else
		game->player.ray.perpWallDist = (game->player.ray.sideDistY - game->player.deltay);
	if(game->player.ray.perpWallDist == 0)
		game->player.ray.perpWallDist = 0.1;	
}



void cal_shadow(t_game *game)
{
	if (game->light_on == 0 && game->player.ray.perpWallDist >= MAX_RENDER_DISTANCE)
			game->player.ray.perpWallDist = MAX_RENDER_DISTANCE;
	else if(game->player.ray.perpWallDist >= MAX_RENDER_DISTANCE * 3)
			game->player.ray.perpWallDist = MAX_RENDER_DISTANCE * 3;

}

void hit_wall_fade(t_game *game, int mapX, int mapY)
{
	game->player.ray.side = 0;
	while (game->map[mapY][mapX] != '1')
	{
		if (game->player.ray.sideDistX < game->player.ray.sideDistY)
		{
			game->player.ray.sideDistX += game->player.deltax;
			mapX += game->player.ray.stepX;
			game->player.ray.side = 0;
		}else
		{
			game->player.ray.sideDistY += game->player.deltay;
			mapY += game->player.ray.stepY;
			game->player.ray.side = 1;
		}
	}
		calculate_distance(game);
		cal_shadow(game);
}

void hit_wall(t_game *game, int mapX, int mapY)
{
	while(game->map[mapY][mapX] != '1' || game->map[mapY][mapX] != '2')
	{
		if (game->player.ray.sideDistX < game->player.ray.sideDistY)
		{
			game->player.ray.sideDistX += game->player.deltax;
			mapX += game->player.ray.stepX;
			game->player.ray.side = 0;
		}
		else
		{
			game->player.ray.sideDistY += game->player.deltay;
			mapY += game->player.ray.stepY;
			game->player.ray.side = 1;
		}
		if(game->map[mapY][mapX] == '1')
		{
			game->hit_door = false;
			break;
		}else if(game->map[mapY][mapX] == '2')
		{
			game->hit_door = true;
			break;
		}
	}
	calculate_distance(game);
}




void draw_ray(t_game *game, double angle)
{
    double cameraX;
	int mapX;
	int mapY;

    game->player.ray.currentRayX = angle;
    cameraX = 2 * angle / WIDTH - 1;
    double rayDirX = game->player.dirX + game->player.camera.PlaneX * cameraX;
    double rayDirY = game->player.dirY + game->player.camera.PlaneY * cameraX;
    game->player.ray.rayDirX = rayDirX;
    game->player.ray.rayDirY = rayDirY;
    game->player.deltax = fabs(1 / rayDirX);
    game->player.deltay = fabs(1 / rayDirY);
	mapX= (int)game->player.PosX;
    mapY = (int)game->player.PosY;
    calculate_ray(game, mapX, mapY);
    hit_wall(game, mapX, mapY);
    game->player.ray.lineheight = (int)(HEIGHT / game->player.ray.perpWallDist);
    game->player.ray.drawStart = -game->player.ray.lineheight / 2 + HEIGHT / 2;
    if(game->player.ray.drawStart < 0)
        game->player.ray.drawStart = 0;
    game->player.ray.drawEnd = game->player.ray.lineheight / 2 + HEIGHT / 2;
    if(game->player.ray.drawEnd >= HEIGHT || game->player.ray.drawEnd < 0)
        game->player.ray.drawEnd = HEIGHT - 1;
    draw_texture(game, angle);
	draw_skyfloor(game,angle,game->player.ray.drawEnd,1);
}



void draw_allray(t_game *game)
{
	int	x;

	x = 0;
	while(x < WIDTH)
	{
		draw_ray(game, x);
		x++;
	}
	// draw_minimap(game);
	draw_flashlight(game);
	mlx_put_image_to_window(game->mlx,game->win, game->canva.img, 0, 0);
}






int	key_event(int keycode, t_game *game)
{
	mouse_monitor(game, keycode);
	define_mov(game, keycode);
	draw_allray(game); 
	if(keycode == ESC)
	{
		system("pkill paplay > /dev/null 2>&1");
		game->status_free = FINAL;
		printf("Status game %i", game->status_free);
		mlx_do_key_autorepeaton(game->mlx);
		garabe_collector(game);
		destroy_game(game);
		exit(0);
	}
	if(game->map[(int)game->player.PosY][(int)game->player.PosX] == '1')
		printf("bateu\n");
	if(game->map[(int)game->player.PosY][(int)game->player.PosX] == 'G')
		dprintf(2, "Abrir Porta\n");
	return (0);
}



void start_window(t_game *game)
{

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->canva.img = mlx_new_image(game->mlx, WIDTH,HEIGHT);
	game->canva.addr = mlx_get_data_addr(game->canva.img,
			&game->canva.bits_per_pixel,
			&game->canva.line_length,
			&game->canva.endian);
	game->status_free = MLX;
	
	load_wall(game);
	ingame(game);
}


