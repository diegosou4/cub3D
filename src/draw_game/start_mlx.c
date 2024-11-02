

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
	if(color == SKY_COLOR)
	{
		if(x > 0)
		{
			while(y < x)
			{
				my_mlx_pixel_put(&game->canva, angle, y, give_color(game, 0));
				y++;
			}
		}
		return;	
	}
	if(color == FLOOR_COLOR)
	{
		if(x < HEIGHT)
		{
			while(x < HEIGHT)
			{
				my_mlx_pixel_put(&game->canva, angle, x, give_color(game, 1));
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

void draw_floor_texture(t_game *game, double angle, int drawEnd)
{
    double rayDirX0 = game->player.dirX - game->player.camera.PlaneX;
    double rayDirY0 = game->player.dirY - game->player.camera.PlaneY;
    double rayDirX1 = game->player.dirX + game->player.camera.PlaneX;
    double rayDirY1 = game->player.dirY + game->player.camera.PlaneY;

    double posZ = 0.5 * HEIGHT;

    for (int y = drawEnd; y < HEIGHT; y++)
    {
        double p = y - HEIGHT / 2;
        double rowDistance = posZ / p;

        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;

        double floorX = game->player.PosX + rowDistance * rayDirX0;
        double floorY = game->player.PosY + rowDistance * rayDirY0;

        for (int x = 0; x < WIDTH; x++)
        {
            int cellX = (int)floorX;
            int cellY = (int)floorY;

            int tx = (int)(64 * (floorX - cellX)) & (64 - 1);
            int ty = (int)(64 * (floorY - cellY)) & (64 - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            // Directly access pixel data from the texture
            char *color_pixel = game->floor.texture.addr + (ty * game->floor.texture.line_length + tx * (game->floor.texture.bits_per_pixel / 8));
            unsigned int color = *(unsigned int *)color_pixel;

            // Put the pixel on the screen
            char *dst_pixel = game->canva.addr + (y * game->canva.line_length + x * (game->canva.bits_per_pixel / 8));
            *(unsigned int *)dst_pixel = color;
        }
    }
}




void draw_ceiling_texture(t_game *game, double angle, int drawStart)
{
    double rayDirX0 = game->player.dirX - game->player.camera.PlaneX;
    double rayDirY0 = game->player.dirY - game->player.camera.PlaneY;
    double rayDirX1 = game->player.dirX + game->player.camera.PlaneX;
    double rayDirY1 = game->player.dirY + game->player.camera.PlaneY;

    double posZ = 0.5 * HEIGHT;

    for (int y = 0; y < drawStart; y++)
    {
        double p = HEIGHT / 2 - y;
        double rowDistance = posZ / p;

        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;

        double floorX = game->player.PosX + rowDistance * rayDirX0;
        double floorY = game->player.PosY + rowDistance * rayDirY0;

        for (int x = 0; x < WIDTH; x++)
        {
            int cellX = (int)floorX;
            int cellY = (int)floorY;

            int tx = (int)(64 * (floorX - cellX)) & (64 - 1);
            int ty = (int)(64 * (floorY - cellY)) & (64 - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            // Directly access pixel data from the texture
            char *color_pixel = game->ceiling.texture.addr + (ty * game->ceiling.texture.line_length + tx * (game->ceiling.texture.bits_per_pixel / 8));
            unsigned int color = *(unsigned int *)color_pixel;

            // Put the pixel on the screen
            char *dst_pixel = game->canva.addr + (y * game->canva.line_length + x * (game->canva.bits_per_pixel / 8));
            *(unsigned int *)dst_pixel = color;
        }
    }
}


void draw_floor_ceiling(t_game *game, double angle)
{
    int y;
    for (y = game->player.ray.drawEnd + 1; y < HEIGHT; y++)
    {
        double currentDist = HEIGHT / (2.0 * y - HEIGHT);  // Current distance from the player to the floor/ceiling

        double weight = currentDist / game->player.ray.perpWallDist;  // Weight factor for averaging

        double floorX = weight * game->player.ray.rayDirX + (1.0 - weight) * game->player.PosX;
        double floorY = weight * game->player.ray.rayDirY + (1.0 - weight) * game->player.PosY;

        int texX, texY;
		int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        texX = (int)(64 * (floorX - cellX)) & (64 - 1);
       	texY = (int)(64 * (floorY - cellY)) & (64 - 1);

        int floorColor = my_mlx_pixel_get(&game->floor.texture, texX, texY);
        int ceilingColor = my_mlx_pixel_get(&game->ceiling.texture, texX, texY);

        my_mlx_pixel_put(&game->canva, angle, y, floorColor);
        my_mlx_pixel_put(&game->canva, angle, HEIGHT - y - 1, ceilingColor);
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
	
	draw_skyfloor(game,angle,game->player.ray.drawEnd,SKY_COLOR);
    draw_texture(game, angle);
	draw_skyfloor(game,angle,game->player.ray.drawEnd,FLOOR_COLOR);
}


void	paintcanva2(t_game *varg, int color, int sx, int sy)
{
	int	x;
	int	y;

	y = 0;
	while (y < 30)
	{
		x = 0;
		while (x < 30)
		{
			my_mlx_pixel_put(&varg->canva, sx + x, sy + y, color);
			x++;
		}
		y++;
	}
}

/* void clear_screen0(t_game *game, double angle) 
{
	int width = game.;
    int height = mlx->height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            my_mlx_pixel_put(mlx, x, y, 0x000000); // Clear to black
        }
    }
} */

void draw_allray(t_game *game)
{
	int	x;
	int y;

	x = 0;
	while(x < WIDTH)
	{
		draw_ray(game, x);
		x++;
	}
	draw_minimap(game);
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
	game->player.textura = aux_load("assets/xpm/player.xpm", game);

	load_wall(game);
	init_ray(game);
	draw_map(game,0);

	// printf_debug(game);
	draw_allray(game);
	
	

	//draw_minimap(game);   //verifica a posição do rato na janela
	mlx_hook(game->win, 2, (1L << 0), key_event, game);
	mlx_hook(game->win, 3, (1L << 1), key_drop, game);
	mlx_hook(game->win, 6, (1L << 6), mouse_track, game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop_hook(game->mlx, mouse_monitor, game);	//consoante a mudança de posição ela executa um movimento
	mlx_loop(game->mlx);
}
