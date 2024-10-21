

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
void calculate_distance(t_game *game, int mapX, int mapY)
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

void hit_wall(t_game *game, int mapX, int mapY)
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

}

void draw_skyfloor(t_game *game,double angle,double x, int color)
{
	int y = 0;
	if(color == BACK_YELLOW)
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
	if(color == DIRT_YELLOW)
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
}

void draw_skyfall(t_game *game, double angle, double drawEnd, t_img *texture, int is_sky)
{
    int y;
    double texture_y;
    double step;
    double texture_pos;
    
    // Determine the starting point and step for texture sampling
    if (is_sky)
    {
        y = 0;
        step = 1.0 * texture->img_height / (drawEnd - y);
        texture_pos = 0;
    }
    else
    {
        y = drawEnd;
        step = 1.0 * texture->img_height / (HEIGHT - drawEnd);
        texture_pos = 0;
    }
    
    while ((is_sky && y < drawEnd) || (!is_sky && y < HEIGHT))
    {
        texture_y = (int)texture_pos & (texture->img_height - 1);
		texture_pos += step;
        int color = my_mlx_pixel_get(texture, (int)angle % texture->img_width, (int)texture_y);
        my_mlx_pixel_put(&game->canva, (int)angle, y, color);
        y++;
    }
}


void draw_ray(t_game *game, double angle)
{
	double cameraX;
	game->player.ray.currentRayX = angle;
	cameraX = 2 * angle / WIDTH - 1;
	double rayDirX = game->player.dirX + game->player.camera.PlaneX * cameraX;
	double rayDirY = game->player.dirY + game->player.camera.PlaneY * cameraX;
	game->player.ray.rayDirX = rayDirX;
	game->player.ray.rayDirY = rayDirY;
	game->player.deltax = fabs(1 / rayDirX);
	game->player.deltay = fabs(1 / rayDirY);

	int mapX = (int)game->player.PosX;
	int mapY = (int)game->player.PosY;
	calculate_ray(game, mapX, mapY);
	hit_wall(game, mapX, mapY);
	game->player.ray.lineheight = (int)(HEIGHT / game->player.ray.perpWallDist);
	
	game->player.ray.drawStart = -game->player.ray.lineheight / 2 + HEIGHT / 2;
	if(game->player.ray.drawStart < 0)
		game->player.ray.drawStart = 0;
	game->player.ray.drawEnd = game->player.ray.lineheight / 2 + HEIGHT / 2;
	if(game->player.ray.drawEnd >= HEIGHT)
		game->player.ray.drawEnd = HEIGHT - 1;
	draw_skyfloor(game,angle,game->player.ray.drawEnd,BACK_YELLOW);
   	draw_texture(game, angle);
	draw_skyfloor(game,angle,game->player.ray.drawEnd,DIRT_YELLOW);
}
void draw_allray(t_game *game)
{
	int x;
	
	x = 0;

	int mapX = (int)game->player.PosX;
	int mapY = (int)game->player.PosY;

	
	//clear_screen(game);

	// aqui no caso 
	while(x < WIDTH)
	{
		draw_ray(game, x);
		x++;
	}
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
	game->mov = mov;
}

int	key_drop(int keycode, t_game *game)
{
	if (keycode == KEY_W && (game->y_mov == 0 || game->y_mov == -1))
	{
		game->y_mov += 1;
		game->N = 0;
	}	
	if (keycode == KEY_S && (game->y_mov == 0 || game->y_mov == 1))
	{
		game->y_mov -= 1;
		game->S = 0;
	}
	if (keycode == KEY_A && (game->x_mov == 0 || game->x_mov == -1))
	{
		game->x_mov += 1;
		game->O = 0;
	}
	if (keycode == KEY_D && (game->x_mov == 0 || game->x_mov == 1)) 
	{
		game->x_mov -= 1;
		game->E = 0;
	}	
	dprintf(2, "x_mov ->%i\n", game->x_mov);
	dprintf(2, "y_mov ->%i\n", game->y_mov);
	return (0);
}


int	key_event(int keycode, t_game *game)
{
	define_mov2(game, keycode);
	//(void)player_mov2(game, keycode);
	//(void)player_mov2(game, keycode);
/* 	if (game && game->mov != 0)
		(void)player_mov2(keycode, game);
	draw_allray(game); */
	// draw_minimap(game);
	if(keycode == ESC)
	{
		game->status_free = FINAL;
		printf("Status game %i", game->status_free);
		mlx_do_key_autorepeaton(game->mlx);
		garabe_collector(game);
		printf("ESC\n");
		exit(0);
	}
	if(game->map[(int)game->player.PosY][(int)game->player.PosX] == '1')
		printf("bateu\n");
	return (0);
}

void printf_debug(t_game *game)
{
	printf("Posicao X %f\n", game->player.PosX);
	printf("Posicao Y %f\n", game->player.PosY);
	printf("Dir X %f\n", game->player.dirX);
	printf("Dir Y %f\n", game->player.dirY);
	printf("Plane X %f\n", game->player.camera.PlaneX);
	printf("Plane Y %f\n", game->player.camera.PlaneY);
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

	load_wall(game);

	init_ray(game);
	draw_map(game,0);

	// printf_debug(game);
	draw_allray(game);
	
	

	// draw_minimap(game);   //verifica a posição do rato na janela
	mlx_hook(game->win, 2, (1L << 0), key_event, game);
	mlx_hook(game->win, 3, (1L << 1), key_drop, game);
	mlx_hook(game->win, 6, (1L << 6), mouse_track, game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop_hook(game->mlx, mouse_monitor, game);	//consoante a mudança de posição ela executa um movimento
	mlx_loop(game->mlx);
}

t_img	load_img(t_game *game, int texture)
{
	t_img	img;

	img.relative_path = game->wall[texture].texture.relative_path;
	img.img = mlx_xpm_file_to_image(game->mlx, img.relative_path,
			&img.img_width, &img.img_height);
	if (img.img == NULL)
	{
		free_walls(game, texture - 1);
		destroy_game(game);
		garabe_collector(game);
		exit(0);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	return (img);
}

void load_wall(t_game *game)
{
	int i;

	i = 0;
	while (i != 4)
	{
		game->wall[i].texture = load_img(game, i);
		i++;
	}
	printf("Paredes carregadas com sucesso\n");
}

t_img	aux_load(t_game *game)
{
	t_img img;

	img.img = mlx_xpm_file_to_image(game->mlx, img.relative_path,
			&img.img_width, &img.img_height);
	if (img.img == NULL)
	{
		free_walls(game, 1);
		destroy_game(game);
		garabe_collector(game);
		exit(0);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	return (img);
}

void load_floor(t_game *game)
{
	game->floor.texture = aux_load(game);
}

void load_ceiling(t_game *game)
{
	game->ceiling.texture = aux_load(game);
}