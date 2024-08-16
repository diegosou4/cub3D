

#include "../../includes/cub3D.h"

void test_player(t_game *game, int color)
{

	for(int i = 0; i < TAM_X_P - 24; i++)
	{
		for(int j = 0; j < TAM_Y_P - 24; j++)
		{
			my_mlx_pixel_put(&game->canva, game->player.x + i, game->player.y + j, color);
		}
	}
}

int	key_event(int keycode, t_game *game)
{
	if(keycode == KEY_W)
	{
		test_player(game,0xfdfdfd);
		game->player.y -= TAM_Y_P - 24;
		test_player(game,0xcb1313);
		mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
	}
	if(keycode == KEY_S)
	{
		test_player(game,0xfdfdfd);
		game->player.y += TAM_Y_P - 24;
		test_player(game,0xcb1313);
		mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
	}
	if(keycode == KEY_D)
	{
		test_player(game,0xfdfdfd);
		game->player.x += TAM_X_P - 24;
		test_player(game,0xcb1313);
		mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
	}
	if(keycode == KEY_A)
	{
		test_player(game,0xfdfdfd);
		game->player.x -= TAM_X_P - 24;
		test_player(game,0xcb1313);
		mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
	}
	if(keycode == ESC)
	{
		printf("ESC\n");
		exit(0);
	}
}
void draw(int x,int y, int color, t_game *game)
{
	int i;
	int j;

	i = 0;
	while(i <= TAM_X_P)
	{
		j = 0;
		while(j <= TAM_Y_P)
		{
			my_mlx_pixel_put(&game->canva, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_map(t_game *game)
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
			else if(game->map[i][j] == '0' || game->map[i][j] == 'N')
				draw(x,y,0xfdfdfd,game);		
			j++;
			x += TAM_X_P;
		}
	
		y += TAM_Y_P;
		i++;
	}
}

void start_window(t_game *game)
{

    game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1280, 720, "Cub3D");
	game->canva.img = mlx_new_image(game->mlx, 1280,720);
	game->canva.addr = mlx_get_data_addr(game->canva.img,
			&game->canva.bits_per_pixel,
			&game->canva.line_length,
			&game->canva.endian);

	load_wall(game);
	
	mlx_put_image_to_window(game->mlx,game->win, game->canva.img, 0, 0);	

	
	game->player.direction = 0;
	game->player.FOV = 60;
	draw_map(game);
	test_player(game,0xcb1313);
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