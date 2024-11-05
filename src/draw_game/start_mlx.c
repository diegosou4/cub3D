

#include "../../includes/cub3D.h"



/// Esse e o Ray casting meu amiigo
// COmeca na funcao de baixo que  
// e um while dentro da horizontal
// o Angle na realidade e o x dentro da tela
// Ta errado o significado aqui
// Prestar atencao nisso
//

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

// aqui e onde calculamos a distancia do raio
// ate a parede
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


// Aqui e onde a magica acontece
// percorre o mapa ate encontrar uma parede
// define se o raio cruzou uma parede horizontal ou vertical

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
		}
		else
		{
			game->player.ray.sideDistY += game->player.deltay;
			mapY += game->player.ray.stepY;
			game->player.ray.side = 1;
		}
		calculate_distance(game, mapX, mapY);
		if (game->light_on == 0)
		{
			if (game->player.ray.perpWallDist >= MAX_RENDER_DISTANCE)
			{
				game->player.ray.perpWallDist = MAX_RENDER_DISTANCE;
				break;
			}
		}
		else 
		{
			if (game->player.ray.perpWallDist >= MAX_RENDER_DISTANCE * 3)
			{
				game->player.ray.perpWallDist = MAX_RENDER_DISTANCE * 3;
		   		break;
			}
		}
	}
}

void hit_wall(t_game *game, int mapX, int mapY)
{
	game->player.ray.side = 0;
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


void draw_skyfloor1(t_game *game,double angle,double x, int color)
{
	int y = 0;
	if(color == TETO && game->light_on)
	{
		if(x > 0)
		{
			while(y < x)
			{
				my_mlx_pixel_put(&game->canva, angle, y, color);
				y++;
			}
		}
		return;	
	}
	else if (color == TETO && !game->light_on)
	{
		if(x > 0)
		{
			while(y < x)
			{
				my_mlx_pixel_put(&game->canva, angle, y, RBG_BLACK);
				y++;
			}
		}
		return;	
	}
	if(color == FLOOR && game->light_on)
	{
		if(x < HEIGHT)
		{
			while(x < HEIGHT)
			{
				my_mlx_pixel_put(&game->canva, angle, x, color);
				x++;
			}
		}
	}
	else if (color == FLOOR && !game->light_on)
	{
		if(x < HEIGHT)
		{
			while(x < HEIGHT)
			{
				my_mlx_pixel_put(&game->canva, angle, x, 0x424242);
				x++;
			}
		}
	}
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
	//hit_wall_fade(game, mapX, mapY);
    hit_wall(game, mapX, mapY);
    game->player.ray.lineheight = (int)(HEIGHT / game->player.ray.perpWallDist);
    game->player.ray.drawStart = -game->player.ray.lineheight / 2 + HEIGHT / 2;
    if(game->player.ray.drawStart < 0)
        game->player.ray.drawStart = 0;
    game->player.ray.drawEnd = game->player.ray.lineheight / 2 + HEIGHT / 2;
    if(game->player.ray.drawEnd >= HEIGHT || game->player.ray.drawEnd < 0)
        game->player.ray.drawEnd = HEIGHT - 1;
	draw_skyfloor1(game,angle,game->player.ray.drawEnd, TETO);
    draw_texture(game, angle);
	draw_skyfloor1(game,angle,game->player.ray.drawEnd, FLOOR);
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
	draw_minimap(game);
	draw_flashlight(game);
	mlx_put_image_to_window(game->mlx,game->win, game->canva.img, 0, 0);
}

void	define_mov2(t_game *game, int keycode)
{
	int	mov;

	mov = IDL;
	if (keycode == KEY_A)
	{
		game->x_mov -= 1;
		game->O = 1;
	}	
	else if (keycode == KEY_D)
	{
		game->x_mov += 1;
		game->E = 1;
	}	
	else if (keycode == KEY_W)
	{
		game->y_mov -= 1;
		game->N = 1;
	}
	else if (keycode == KEY_S)
	{
		game->y_mov += 1;
		game->S = 1;
	}
	else if (keycode == L_AR)
		game->rot_Left = 1;
	else if (keycode == R_AR)
		game->rot_Right = 1;
	else if (keycode == KEY_F)
	{
		if (game->light_on == 0)
			game->light_on = 1;
		else 
			game->light_on = 0;
	}
	game->mov = mov;
}

int	key_drop(int keycode, t_game *game)
{
	if (keycode == KEY_W && (game->y_mov == 0 || game->y_mov == -1))
	{
		//game->light_on = 0;
		game->y_mov += 1;
		game->N = 0;
	}	
	if (keycode == KEY_S && (game->y_mov == 0 || game->y_mov == 1))
	{
		//game->light_on = 0;
		game->y_mov -= 1;
		game->S = 0;
	}
	if (keycode == KEY_A && (game->x_mov == 0 || game->x_mov == -1))
	{
		//game->light_on = 0;
		game->x_mov += 1;
		game->O = 0;
	}
	if (keycode == KEY_D && (game->x_mov == 0 || game->x_mov == 1)) 
	{
		//game->light_on = 0;
		game->x_mov -= 1;
		game->E = 0;
	}
	if (game->rot_Left == 1 && keycode == L_AR)
		game->rot_Left = 0;
	if (game->rot_Right == 1 && keycode == R_AR)
		game->rot_Right = 0;
	return (0);
}


int	key_event(int keycode, t_game *game)
{
	mouse_monitor(game, keycode);
	define_mov2(game, keycode);
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

void printf_debug(t_game *game)
{
	printf("\n");
	printf("Posicao X %f\n", game->player.PosX);
	printf("Posicao Y %f\n", game->player.PosY);
	printf("Dir X %f\n", game->player.dirX);
	printf("Dir Y %f\n", game->player.dirY);
	printf("Plane X %f\n", game->player.camera.PlaneX);
	printf("Plane Y %f\n", game->player.camera.PlaneY);
	printf("\n");
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


/* void hit_wall(t_game *game, int mapX, int mapY)
{
	game->player.ray.side = 0;
	while(game->map[mapY][mapX] != '1')
	{
		if(game->player.ray.sideDistX < game->player.ray.sideDistY)
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
			break;
	}
	calculate_distance(game, mapX, mapY);
} */