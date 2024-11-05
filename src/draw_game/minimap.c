#include "../../includes/cub3D.h"

void	update_player_sprite(t_game *img)
{
	img->player.curr_frame = (img->player.curr_frame + 1) % img->player.sprite_num;
}

void	paint_player(t_game *vars, t_img *img, int x, int y)
{
	int	frame_x_offset;
	int	frame_y_offset;
	int	sy;
	int	sx;
	int	color;

	frame_x_offset = (vars->player.curr_frame % vars->player.sprite_num) * WIDTH;
	frame_y_offset = 20;
	sy = 0;
	while (sy < HEIGHT)
	{
		sx = 0;
		while (sx < WIDTH)
		{
			color = my_mlx_pixel_get(img, frame_x_offset + sx, frame_y_offset
					+ sy);
			my_mlx_pixel_put(&vars->canva, x + sx, y + sy, color);
			sx++;
		}
		sy++;
	}
}

static void	__render(t_game *this, int sx, int sy)
{
	update_player_sprite(this);
	paint_player(this, &this->player.sprites[0].texture, sx, sy);
}


void draw_flashlight(t_game *game) 
{
	int x, y;
	double frequency = 0.05; 
	double amplitude = 10.0;
	double vertical_offset = sin(game->frameCtd * frequency) * amplitude;

	y = 0;

	while (y < game->player.sprites[1].texture.img_height && game->light_on) {
		x = 0;
		while (x < game->player.sprites[1].texture.img_width) {
			my_mlx_pixel_put(&game->canva, WIDTH / 2 + x, (HEIGHT / 2 + 150 + (int)vertical_offset) + y, my_mlx_pixel_get(&game->player.sprites[1].texture, x, y));
			x++;
		}
		y++;
	}
	game->frameCtd++;
}

void draw_minimap(t_game *game) 
{
	int map_height;
	int minimap_radius;
	int player_minimap_x;
	int player_minimap_y;
	int map_x_int;
	int map_y_int;
	int row_length;
	int y;
	int x;
	double start_map_x;
	double start_map_y;
	double end_map_x;
	double end_map_y;
	double map_x;
	double map_y;

	map_height = 0;
	while (game->map[map_height] != NULL)
		map_height++;
	minimap_radius = MINIMAP_SIZE / 2;
	player_minimap_x = MINIMAP_SIZE / 2;
	player_minimap_y = MINIMAP_SIZE / 2;

	start_map_x = game->player.PosX - minimap_radius / (MINIMAP_SCALE * TILE_SIZE);
	start_map_y = game->player.PosY - minimap_radius / (MINIMAP_SCALE * TILE_SIZE);
	end_map_x = game->player.PosX + minimap_radius / (MINIMAP_SCALE * TILE_SIZE);
	end_map_y = game->player.PosY + minimap_radius / (MINIMAP_SCALE * TILE_SIZE);

	y = 0;
	while (y < MINIMAP_SIZE) 
	{
		x = 0;
		while(x < MINIMAP_SIZE) 
		{
			map_x = start_map_x + x / (MINIMAP_SCALE * TILE_SIZE);
			map_y = start_map_y + y / (MINIMAP_SCALE * TILE_SIZE);

			map_x_int = (int)map_x;
			map_y_int = (int)map_y;


			if (map_x_int >= 0 && map_y_int >= 0 && map_y_int < map_height) 
			{
				row_length = ft_strlen(game->map[map_y_int]);
				if (map_x_int < row_length) 
				{
					if (game->map[map_y_int][map_x_int] == '1')
						my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, 0xFFFFFF);
					else if (game->map[map_y_int][map_x_int] == '0')
						my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, 0x000000);
					else if (game->map[map_y_int][map_x_int] == 'S' || game->map[map_y_int][map_x_int] == 'N' || game->map[map_y_int][map_x_int] == 'E' \
							|| game->map[map_y_int][map_x_int] == 'O')
						my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, RBG_YELLOW);
				}
			} 
			x++;
		}
		//__render(game,  player_minimap_x + TILE_SIZE, player_minimap_y + TILE_SIZE);
		paintimage(game, &game->player.sprites[0].texture, player_minimap_x + TILE_SIZE, player_minimap_y + TILE_SIZE);
	}
}




/* void draw_minimap(t_game *game)
{
	int map_width = ft_strlen(game->map[0]);
	int map_height = 0;
	while (game->map[map_height] != NULL)
	{
		map_height++;
	}
	int minimap_radius = MINIMAP_SIZE / 2;
	int player_minimap_x = MINIMAP_SIZE / 2 - game->player.char_minimap.img_width / 2;
	int player_minimap_y = MINIMAP_SIZE / 2 - game->player.char_minimap.img_height / 2;

	// Calculate start and end points for the minimap view based on player's position
	double start_map_x = game->player.PosX - minimap_radius / (MINIMAP_SCALE * TAM_X_P);
	double start_map_y = game->player.PosY - minimap_radius / (MINIMAP_SCALE * TAM_Y_P);

	// Draw the minimap background (walls and empty spaces)
	for (int y = 0; y < MINIMAP_SIZE; y++)
	{
		for (int x = 0; x < MINIMAP_SIZE; x++)
		{
			double map_x = start_map_x + x / (MINIMAP_SCALE * TAM_X_P);
			double map_y = start_map_y + y / (MINIMAP_SCALE * TAM_Y_P);

			int map_x_int = (int)map_x;
			int map_y_int = (int)map_y;

			if (map_x_int >= 0 && map_x_int < map_width && map_y_int >= 0 && map_y_int < map_height)
			{
				if (game->map[map_y_int][map_x_int] == '1')
					my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, RBG_YELLOW); // White color for walls
				else
					my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, DIRT_YELLOW); // Black color for empty space
			}
			else
				my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, 0x000000); // Black for out of bounds
		}
	}
	paintimage(game, &game->player.char_minimap, player_minimap_x + MINIMAP_MARGIN, player_minimap_y + MINIMAP_MARGIN);
} */
