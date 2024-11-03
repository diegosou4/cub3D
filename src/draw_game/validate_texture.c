



#include "../../includes/cub3D.h"

int hex_color(t_game *game, int pos)
{
    return(game->color[pos].r << 16 | game->color[pos].g << 8 | game->color[pos].b);
}

void draw_skyfloor(t_game *game,double angle,double x, int pos)
{
	int y = 0;
	if(pos == 0)
	{
		if(x > 0)
		{
			while(y < x)
			{
				my_mlx_pixel_put(&game->canva, angle, y,  hex_color(game, pos));
				y++;
			}
		}
		return;	
	}
	if(pos == 1)
	{
		if(x < HEIGHT)
		{
			while(x < HEIGHT)
			{
				my_mlx_pixel_put(&game->canva, angle, x,  hex_color(game, pos));
				x++;
			}
		}
	}
}

t_img	load_img(t_game *game, char *path)
{
	t_img	img;

	img.relative_path = path;
	img.img = mlx_xpm_file_to_image(game->mlx, img.relative_path,
			&img.img_width, &img.img_height);
	if (img.img == NULL)
	{
		printf("Nao conseguiu ler nem a imagem %s\n", img.relative_path);
		free_walls(game);
		garabe_collector(game);
		destroy_game(game);
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
	game->current_img = 0;
	while (i != 12)
	{
		game->current_img = i;
		game->wall[i].texture = load_img(game, game->wall[i].texture.relative_path);
		printf("Morre aqui\n");
		i++;
	}
	printf("chegamos aqui\n");
}