


#include "../../includes/cub3D.h"


void  	init_ray(t_game *game)
{
	float x;
	float y;
	float distance;
	game->player.camera.PlaneX = 0;
	game->player.camera.PlaneY = 0;
	game->player.deltax = 0;
	game->player.deltay = 0;
	game->player.dirX = 0;
	game->player.dirY = 0;
	game->player.time.time = 0;
	game->player.time.oldtime = 0;
	game->player.time.frametime = 0;
    game->player.ray.rayDirX = 0;
    game->player.ray.rayDirY = 0;
    game->player.ray.sideDistX = 0;
    game->player.ray.sideDistY = 0;
    game->player.ray.deltaDistX = 0;
    game->player.ray.deltaDistY = 0;
    game->player.ray.perpWallDist = 0;
    game->player.ray.stepX = 0;
    game->player.ray.stepY = 0;
    game->player.ray.hit = 0;
    game->player.ray.side = 0;
    game->player.ray.lineheight = 0;
    game->player.ray.drawStart = 0;
    game->player.ray.drawEnd = 0;
	game->N = 0;
	game->S = 0;
	game->E = 0;
	game->O = 0;
}


void define_direction(t_game *game , char direction)
{
	if (direction == 'N')
	{
		game->player.camera.PlaneX = 0.66;
		game->player.dirY = -1;
	}
	else if (direction == 'S')
	{
		game->player.camera.PlaneX = -0.66;
		game->player.dirY = 1;
	}
	else if (direction == 'W')
	{
		game->player.camera.PlaneY = -0.66;
		game->player.dirX = -1;
	}
	else if (direction == 'E')
	{
		game->player.camera.PlaneY = 0.66;
		game->player.dirX = 1;
	}
}


void draw_map(t_game *game, int ftime)
{
	int i;
	int j;
	int x;
	int y;
	x = 0;
	y = 0;
	int size = 0;
	while(game->map[size] != NULL)
		size++;
	i = 0;
	while (i < size)
	{
		x = 0;
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			if(game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				if(ftime == 0)
				{
					define_direction(game,game->map[i][j]);
					game->player.PosX = j;
					game->player.PosY = i;
					game->player.Px = x + 8;
					game->player.Py = y + 8;
				}
			}	
			j++;
			x += TAM_X_P;
		}
		y += TAM_Y_P;
		i++;
	}
}