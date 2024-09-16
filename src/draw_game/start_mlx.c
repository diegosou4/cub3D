

#include "../../includes/cub3D.h"

void draw(int x,int y, int color, t_game *game)
{
	int i;
	int j;

	i = 0;
	while(i < TAM_X_P)
	{
		j = 0;
		while(j < TAM_Y_P)
		{
			my_mlx_pixel_put(&game->canva, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void define_direction(t_game *game , char direction)
{
	if (direction == 'N')
		game->player.direction = A_NORTH;
	else if (direction == 'S')
		game->player.direction = A_SOUTH;
	else if (direction == 'W')
		game->player.direction = A_WEST;
	else if (direction == 'E')
		game->player.direction = A_EAST;
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
			if(game->map[i][j] == '1')
				draw(x,y,808080,game);
			else if(game->map[i][j] == '0')
				draw(x,y,0xfdfdfd,game);
			else if(game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				if(ftime == 0)
				{
					define_direction(game,game->map[i][j]);
					game->player.PosX = j;
					game->player.PosY = i;
					game->player.Px = x;
					game->player.Py = y;
				}
				draw(x,y,0xfdfdfd,game);
			}	
			j++;
			x += TAM_X_P;
		}
		y += TAM_Y_P;
		i++;
	}
}

void test_player(t_game *game, int color)
{

	for(int i = 0; i < TAM_P; i++)
	{
		for(int j = 0; j < TAM_P; j++)
		{
			my_mlx_pixel_put(&game->canva, game->player.Px + i, game->player.Py + j, color);
		}
	}
}




void  	init_ray(t_game *game)
{
	float x;
	float y;
	float distance;
	game->player.camera.PlaneX = 0;
	game->player.camera.PlaneY = 0.66;
	game->player.deltax = cos(game->player.direction * (M_PI / 180));
	game->player.deltay = sin(game->player.direction * (M_PI / 180));
	game->player.dirX = -1;
	game->player.dirY = 0;
}

void draw_ray(t_game *game, double angle)
{
	float x;
	float y;
	double deltaX;
	double deltaY;
	x = game->player.Px  + (TAM_P / 2);
	y = game->player.Py + (TAM_P / 2);


	deltaX = cos(angle * (M_PI / 180));
	deltaY = sin(angle * (M_PI / 180));


	while(game->map[(int)y / TAM_Y_P][(int)x / TAM_X_P] != '1')
	{
		x += deltaX;
		y += deltaY;
		my_mlx_pixel_put(&game->canva, x, y, BLUE);
	}
}
void draw_allray(t_game *game)
{
	int i; 
	double angle;

	i = 0;

	angle = game->player.direction - FOV / 2;
	while( angle != game->player.direction + FOV / 2)
	{
		draw_ray(game,angle);
		angle++;
	}
}

void dda_algorithm(t_game *game, double rayDirX, double rayDirY)
{


	double detalDistX;
	double detalDistY;

	double deltaDistX = (rayDirX == 0) ? 1e30 : 1 + (rayDirY * rayDirY) / (rayDirX * rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : 1 + (rayDirX * rayDirX) / (rayDirY * rayDirY);
	double distToSizeX;
	double distToSizeY;

	
	
}

void raycasting(t_game *game)
{

	int x;

	double range;
	x = 0;
	
	double mult;

	
	while(x < 1)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = game->player.dirX +  game->player.camera.PlaneX * cameraX;
		double rayDirY = game->player.deltay + game->player.camera.PlaneY * cameraX;
		printf("rayDirX %f\n",rayDirX);
		printf("rayDirY %f\n",rayDirY);


	
		printf("\n\n");
		dda_algorithm(game,rayDirX,rayDirY);
		//mlx_pixel_put(&game->canva, game->win, rayDirX, rayDirY, RED);
		x++;
	}

	

}
// Corigir angulos

int	key_event(int keycode, t_game *game)
{

	player_mov(game, keycode);
	if(keycode == ESC)
	{
		game->status_free = FINAL;
		printf("Status game %i", game->status_free);

		garabe_collector(game);
		printf("ESC\n");
		exit(0);
	}
	if(game->map[game->player.PosY][game->player.PosX] == '1')
		printf("bateu\n");
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
	
	mlx_put_image_to_window(game->mlx,game->win, game->canva.img, 0, 0);	
	
	draw_map(game,0);
	init_ray(game);
		test_player(game,0xcb1313);	
	draw_allray(game);
	
	// draw_allray(game);
	// raycasting(game);

	mlx_put_image_to_window(game->mlx,game->win, game->canva.img, 0, 0);	
	mlx_hook(game->win, 2, 1L << 0, key_event, game);
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