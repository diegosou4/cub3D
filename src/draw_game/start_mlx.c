

#include "../../includes/cub3D.h"

void start_window(t_game *game)
{

    game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "Cub3D");
	game->canva.img = mlx_new_image(game->mlx, 1920,1080);
	game->canva.addr = mlx_get_data_addr(game->canva.img,
			&game->canva.bits_per_pixel,
			&game->canva.line_length,
			&game->canva.endian);

	load_wall(game);
	mlx_put_image_to_window(&game->mlx,&game->win, game->canva.img, 0, 0);
	// mlx_loop(game->mlx);
}

t_img	load_img(t_game *game, int texture)
{
	t_img	img;

	printf("%s path\n", game->wall[texture].texture.relative_path);
	img.relative_path = game->wall[texture].texture.relative_path;
	img.img = mlx_xpm_file_to_image(game->mlx, img.relative_path,
			&img.img_width, &img.img_height);
	if (img.img == NULL)
	{
		printf("Deu ruim papai");
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
	while (i != 3)
	{
		game->wall[i].texture = load_img(game, i);
		i++;
	}
	printf("Paredes carregadas com sucesso\n");
}