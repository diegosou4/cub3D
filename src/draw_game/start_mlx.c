

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

void hit_wall(t_game *game, int mapX, int mapY)
{
	game->player.ray.side = 0;
	while(game->map[mapY][mapX] != '1' || game->map[mapY][mapX] != '2')
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
	if (game->S || game->E || game->N || game->O)
		game->light_on = 1;
	game->mov = mov;
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
