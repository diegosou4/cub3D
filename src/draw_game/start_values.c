


#include "../../includes/cub3D.h"

void init_values2(t_game *game)
{
	int i;
	
	i = -1;
	game->N = 0;
	game->S = 0;
	game->E = 0;
	game->O = 0;
	game->rot_Left = 0;
	game->rot_Right = 0;
	game->frameCtd = 0;
	game->light_on = 0;
	game->current_img = -1;
	game->status_free = PARSE;
	game->x_mouse = WIDTH / 2;
	game->y_mouse = HEIGHT / 2;
	game->curr_map = 0;
	game->hit_door = false;
	game->hit_enemy = false;
	game->current_img = 0;
	game->inside_wall = false;
	game->changed_world = false;
	game->current_world = 0;
	while(++i != NUM_TEXTURE - 1) 
		game->texture[i].filled = false;
}

void  	init_values(t_game *game)
{
	game->player.camera.PlaneX = 0;
	game->player.camera.PlaneY = 0;
	game->player.deltax = 0;
	game->player.deltay = 0;
	game->player.dirX = 0;
	game->player.dirY = 0;
	game->player.ray.ray_dir_x = 0;
	game->player.ray.ray_dir_y = 0;
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
	init_values2(game);
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


void start_map2(t_game *game, int ftime,int i, int y)
{
	int j;
	int x;

	j = 0;
	x = 0;
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
}

void start_map(t_game *game, int ftime)
{
	int i;
	int y;

	y = 0;
	i = 0;
	
	while (i < ft_dstrlen(game->map))
	{
		start_map2(game,ftime,i,y);
		y += TAM_Y_P;
		i++;
	}
}
