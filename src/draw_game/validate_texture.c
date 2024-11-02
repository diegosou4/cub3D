



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