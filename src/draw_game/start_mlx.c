

#include "../../includes/cub3D.h"

void draw(int x,int y, int color, t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	return;	
	my_mlx_pixel_put(&game->canva, x + i, y + j, GRAY_COLOR);
	i++;
	while(i < TAM_X_P)
	{
		j = 0;
		if( j == 0)
		{
			my_mlx_pixel_put(&game->canva, x + i, y + j, GRAY_COLOR);
			j++;
		}
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
					game->player.Px = x + 8;
					game->player.Py = y + 8;
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
void draw_floor(t_game *game)
{
	int i;
	int j;
	i = 0;
	while(i < WIDTH)
	{
		j = 0;
		while(j < HEIGHT / 2)
		{
			my_mlx_pixel_put(&game->canva, i, j, SKY_COLOR);
			j++;
		}
		i++;
	}
	i = 0;
	while(i < WIDTH)
	{
		j = HEIGHT / 2;
		while(j < HEIGHT)
		{
			my_mlx_pixel_put(&game->canva, i, j, GRAY_COLOR);
			j++;
		}
		i++;
	}
}

void test_player(t_game *game, int color)
{
	draw_allray(game);
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
	game->player.deltax = 0;
	game->player.deltay = 0;
	game->player.dirX = 0;
	game->player.dirY = 0;
	game->player.time.time = 0;
	game->player.time.oldtime = 0;
	game->player.time.frametime = 0;
}


/// Esse e o Ray casting meu amiigo
// COmeca na funcao de baixo que  
// e um while dentro da horizontal
// o Angle na realidade e o x dentro da tela
// Ta errado o significado aqui
// Prestar atencao nisso
//


void draw_ray(t_game *game, double angle)
{
	double cameraX;

	cameraX = 2 * angle / WIDTH - 1;
	double rayDirX = game->player.dirX + game->player.camera.PlaneX * cameraX;
	double rayDirY = game->player.dirY + game->player.camera.PlaneY * cameraX;
	game->player.ray.rayDirX = rayDirX;
	game->player.ray.rayDirY = rayDirY;
	game->player.deltax = fabs(1 / rayDirX);
	game->player.deltay = fabs(1 / rayDirY);

	int mapX = (int)game->player.PosX;
	int mapY = (int)game->player.PosY;
	// A partit da qui sao varias matematicas chatas
	//que eu ainda nao entendi 100% devemos olhar com mais calma
	// apenas segui o site que eu estava lendo
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
	game->player.ray.side = 0;
	while(42)
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

	game->player.ray.perpWallDist = 0;

	if(game->player.ray.side == 0)
		game->player.ray.perpWallDist = (mapX - game->player.PosX + (1 - game->player.ray.stepX) / 2) / game->player.ray.rayDirX;
	else
		game->player.ray.perpWallDist = (mapY - game->player.PosY + (1 - game->player.ray.stepY) / 2) / game->player.ray.rayDirY;
	
	game->player.ray.lineheight = (int)(HEIGHT / game->player.ray.perpWallDist);
	
	game->player.ray.drawStart = -game->player.ray.lineheight / 2 + HEIGHT / 2;
	if(game->player.ray.drawStart < 0)
		game->player.ray.drawStart = 0;
	game->player.ray.drawEnd = game->player.ray.lineheight / 2 + HEIGHT / 2;
	if(game->player.ray.drawEnd >= HEIGHT)
		game->player.ray.drawEnd = HEIGHT - 1;
	int color;
	
	color = RBG_RED;
    // if (game->player.ray.side == 1) 
    // {
    //     color = color / 2;
    // }

    for(int y = game->player.ray.drawStart; y < game->player.ray.drawEnd; y++)
    {
        	mlx_pixel_put(game->mlx, game->win, angle, y, color);
    }
	
}
void draw_allray(t_game *game)
{
	int x;
	
	x = 0;

		int mapX = (int)game->player.PosX;
	int mapY = (int)game->player.PosY;

	printf("Posicao do player em x %f\n", game->player.PosX);
	printf("Posicao do player em y %f\n", game->player.PosY);
	
	// aqui no caso 
	while(x < WIDTH)
	{
		draw_ray(game, x);
		x++;
	}
	
	printf("Chegamos aqui\n");
}

// void dda_algorithm(t_game *game, double rayDirX, double rayDirY)
// {


// 	double detalDistX;
// 	double detalDistY;

// 	double deltaDistX = (rayDirX == 0) ? 1e30 : 1 + (rayDirY * rayDirY) / (rayDirX * rayDirX);
//     double deltaDistY = (rayDirY == 0) ? 1e30 : 1 + (rayDirX * rayDirX) / (rayDirY * rayDirY);
// 	double distToSizeX;
// 	double distToSizeY;
	
// }

// void raycasting(t_game *game)
// {

// 	int x;

// 	double range;
// 	x = 0;
	
// 	double mult;

	
// 	while(x < WIDTH)
// 	{
// 		double cameraX = 2 * (x / WIDTH) - 1;
// 		double rayDirX = game->player.dirX +  game->player.camera.PlaneX * cameraX;
// 		double rayDirY = game->player.deltay + game->player.camera.PlaneY * cameraX;
// 		int mapX = (int)game->player.PosX;
//         int mapY = (int)game->player.PosY;

// 		double deltaDistX = fabs(1 / rayDirX);
//         double deltaDistY = fabs(1 / rayDirY);

// 		printf("%f RayDir x \n", rayDirX);
// 		printf("%f RayDir Y \n", rayDirY);
		
// 		double sideDistX;
//         double sideDistY;
// 		int stepX;
//         int stepY;

        
   
// 		x++;
// 	}

	

// }
// Corigir angulos

int	key_event(int keycode, t_game *game)
{

	(void)player_mov(game, keycode);
	mlx_put_image_to_window(game->mlx,game->win, game->canva.img, 0, 0);
	draw_allray(game);

	if(keycode == ESC)
	{
		game->status_free = FINAL;
		printf("Status game %i", game->status_free);

		garabe_collector(game);
		printf("ESC\n");
		exit(0);
	}
	if(game->map[(int)game->player.PosY][(int)game->player.PosX] == '1')
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
	init_ray(game);
	draw_map(game,0);
	
	draw_allray(game);

		// test_player(game,0xcb1313);	


	// mlx_put_image_to_window(game->mlx,game->win, game->canva.img, 0, 0);	
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