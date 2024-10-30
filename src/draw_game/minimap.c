#include "../../includes/cub3D.h"


void	paintcanva(t_game *varg, int color, int sx, int sy)
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
    for (y = 0; y < MINIMAP_HEIGHT; y++)
    {
        for (x = 0; x < MINIMAP_WIDTH; x++)
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
}
