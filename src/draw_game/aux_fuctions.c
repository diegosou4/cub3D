#include "../../includes/cub3D.h"

void	swift_rgb(t_game *game, int color, double fade_factor, int y)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * fade_factor);
	g = (int)(((color >> 8) & 0xFF) * fade_factor);
	b = (int)((color & 0xFF) * fade_factor);
	if (color != -16777216)
	{
		color = (r << 16) | (g << 8) | b;
		my_mlx_pixel_put(&game->canva, (int)game->player.ray.currentRayX, y,
			color);
	}
}

void	bu_timer(t_game *game)
{
	static time_t	last_played_time;
	time_t	current_time;

	current_time = time(NULL);
	if (difftime(current_time, last_played_time) >= 10)
	{
		if (game->playBur != NULL)
			system(game->playBur);
		last_played_time = current_time;
	}
}
