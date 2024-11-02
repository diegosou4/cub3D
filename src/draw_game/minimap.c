#include "../../includes/cub3D.h"


/* void	paintcanva(t_game *varg, int color, int sx, int sy)
{
	int	x;
	int	y;

	y = 0;
	while (y < 30)
	{
		x = 0;
		while (x < 30)
		{
			my_mlx_pixel_put(&varg->canva, sx + x, sy + y, color);
			x++;
		}
		y++;
	}
}

void draw_mini_map(t_game *game)
{
    int y, x;
    int minimap_x, minimap_y;

    // Ensure that the minimap dimensions are within the bounds of the map
    for (y = 1; y < MINIMAP_HEIGHT; y++)
    {
        for (x = 1; x < MINIMAP_WIDTH; x++)
        {
            // Calculate the correct position in the game map
            char tile = game->map[y][x]; // Get the tile character

            minimap_x = x * 30; // Scale to minimap size
            minimap_y = y * 30;

            if (tile == '1') // Wall
                paintcanva(game, RBG_BLACK, minimap_x, minimap_y);
            else if (tile == '0') // Floor
                paintcanva(game, RBG_WHITE, minimap_x, minimap_y);
             else if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E') // Player
            {
                paintcanva(game, RBG_RED, minimap_x, minimap_y); // Draw player in red
            } 
        }
    }
} */

/* void clear_screen(t_game *game) 
{
    int width = game->canva.img_width;
    int height = game->canva.img_height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            my_mlx_pixel_put(&game->canva, x, y, 0x000000); // Clear to black
        }
    }
} */

/* void update_player_position(t_game *game, double new_x, double new_y) {
    game->player.pos_x = new_x;
    game->player.pos_y = new_y;
} */

void draw_beam(t_game *game, double angle)
{
    float x = game->player.Px + (TAM_P / 2);
    float y = game->player.Py + (TAM_P / 2);
    double deltaX = cos(angle * (M_PI / 180));
    double deltaY = sin(angle * (M_PI / 180));

    // Move in the direction of the ray until hitting a wall
    while (ft_strrchr("0NSWE", game->map[(int)(y / TAM_Y_P)][(int)(x / TAM_X_P)]) == 1)
    {
        x += deltaX;
        y += deltaY;
    }

    // Store the final position of the ray
    game->player.deltax = x;
    game->player.deltay = y;
}

void draw_mapray(t_game *game)
{
    int num_rays = 60; // Number of rays for the field of view
    double angle = game->player.direction - (FOV / 2); // Start angle of FOV
    double angle_increment = FOV / num_rays;

    for (int i = 0; i < num_rays; i++)
    {
        draw_beam(game, angle); // Cast ray for current angle

        // Calculate the minimap position for the ray endpoint
        int minimap_ray_x = (int)((game->player.deltax - game->player.PosX) * MINIMAP_SCALE + (MINIMAP_SIZE / 2));
        int minimap_ray_y = (int)((game->player.deltay - game->player.PosY) * MINIMAP_SCALE + (MINIMAP_SIZE / 2));

        // Draw the ray on the minimap if within bounds
        if (minimap_ray_x >= 0 && minimap_ray_x < MINIMAP_SIZE &&
            minimap_ray_y >= 0 && minimap_ray_y < MINIMAP_SIZE) 
        {
            my_mlx_pixel_put(&game->canva, minimap_ray_x + MINIMAP_MARGIN, 
                             minimap_ray_y + MINIMAP_MARGIN, 0xFF0000); // Red color for rays
        }
        
        angle += angle_increment; // Increment angle for the next ray
    }

    draw_minimap(game); // Draw the minimap background and player position
}


void draw_minimap(t_game *game)
{
    int map_width = ft_strlen(game->map[0]);
    int map_height = 0;
    while (game->map[map_height] != NULL)
    {
        map_height++;
    }

    int minimap_radius = MINIMAP_SIZE / 2;
    int player_minimap_x = MINIMAP_SIZE / 2 - game->player.textura.img_width / 2;
    int player_minimap_y = MINIMAP_SIZE / 2 - game->player.textura.img_height / 2;

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
                    my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, FLOOR_MAP); // Black color for empty space
            }
            else
                my_mlx_pixel_put(&game->canva, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN, 0x000000); // Black for out of bounds
        }
    }
    paintimage(game, &game->player.textura, player_minimap_x + MINIMAP_MARGIN, player_minimap_y + MINIMAP_MARGIN);
}



