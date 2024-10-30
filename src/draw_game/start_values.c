


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
	game->rot_Left = 0;
	game->rot_Right = 0;
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

void set_pixel(void *img, int x, int y, int color, int width) {
    char *data;
    int bpp; // Bits per pixel
    int size_line; // Size of a line in bytes
    int endian; // Endianness

    // Get image data
    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    
    if (x >= 0 && x < width && y >= 0) // Ensure x and y are within bounds
        *(unsigned int *)(data + (y * size_line + x * (bpp / 8))) = color;
}

void draw_tile(void *mlx_ptr, void *win_ptr, int x, int y, int tile_size, int color) {
    for (int i = 0; i < tile_size; i++) {
        for (int j = 0; j < tile_size; j++) {
            set_pixel(mlx_ptr, x + j, y + i, color, tile_size);
        }
    }
}

void draw_circle(t_img *img, int cx, int cy, int radius, int color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (sqrt(x * x + y * y) <= radius) { // Check if the point is within the circle
               my_mlx_pixel_put(img, cx + x, cy + y, color); // Set the pixel color
            }
        }
    }
}


void draw_minimap(t_game *game, int minimap_x, int minimap_y, int minimap_width, int minimap_height)
{
    int i, j;
    float scale_x = (float)minimap_width / (WIDTH * TAM_X_P);
    float scale_y = (float)minimap_height / (WIDTH * TAM_Y_P);
    
    for (i = 0; game->map[i] != NULL; i++)
    {
        for (j = 0; j < ft_strlen(game->map[i]); j++)
        {
            char tile = game->map[i][j];
            int minimap_tile_x = minimap_x + (int)(j * TAM_X_P * scale_x);
            int minimap_tile_y = minimap_y + (int)(i * TAM_Y_P * scale_y);
            
            // Draw the tile based on its type
            if (tile == '1') // Wall
				draw(minimap_tile_x, minimap_tile_y,808080,game);
            else if (tile == '0') // Floor
                draw(minimap_tile_x, minimap_tile_y,0xfdfdfd,game); // Example color
            else if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E') // Player
                draw(minimap_tile_x, minimap_tile_y,0xfdfdfd,game);
        }
    }
    // Highlight player position in the minimap
    int player_minimap_x = minimap_x + (int)(game->player.PosX * TAM_X_P * scale_x);
    int player_minimap_y = minimap_y + (int)(game->player.PosY * TAM_Y_P * scale_y);
    draw_circle(&game->canva, player_minimap_x, player_minimap_y, 3, RBG_RED); // Draw player position
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
	//draw_minimap(game, MINIMAP_OFFSET_X, MINIMAP_OFFSET_Y, MINIMAP_WIDTH, MINIMAP_HEIGHT);
}