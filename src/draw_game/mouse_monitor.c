#include "../../includes/cub3D.h"

int mouse_track(int x, int y, t_game *game)
{
	if (game->x_mouse == x && game->y_mouse == y)
		return (0);
	game->x_mouse = x;
	game->y_mouse = y;
	return (0);
}

int mouse_monitor(t_game *game, int keycode)
{
	static int	prev_x_mouse = WIDTH / 2;
	double		deltaX;

	deltaX = game->x_mouse - prev_x_mouse;
	
	if ((game->x_mouse > 0 && game->x_mouse < WIDTH) || keycode == R_AR || keycode == L_AR || keycode == KEY_W \
		|| keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		deltaX = game->x_mouse - prev_x_mouse;
		if (deltaX != 0 || keycode == R_AR || keycode == L_AR)
		{
			if (deltaX > 0 || game->rot_Right == 1)
				arrow_right(game);
			else if ( deltaX < 0 || game->rot_Left == 1)
				arrow_left(game);
			prev_x_mouse = WIDTH /2;
		}
		player_mov(game);
		draw_allray(game);
		//draw_minimap(game);
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	}
	return (1);
}

int arrow_left(t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX; 
	game->player.dirX = game->player.dirX * cos(-ROT_SPEED) - game->player.dirY * sin(-ROT_SPEED);
	game->player.dirY = oldDirX * sin(-ROT_SPEED) + game->player.dirY * cos(-ROT_SPEED);
	oldPlaneX = game->player.camera.PlaneX;
	game->player.camera.PlaneX = game->player.camera.PlaneX * cos(-ROT_SPEED) - game->player.camera.PlaneY * sin(-ROT_SPEED);
	game->player.camera.PlaneY = oldPlaneX * sin(-ROT_SPEED) + game->player.camera.PlaneY * cos(-ROT_SPEED);
	return (1);
}

int arrow_right(t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(ROT_SPEED) - game->player.dirY * sin(ROT_SPEED);
	game->player.dirY = oldDirX * sin(ROT_SPEED) + game->player.dirY * cos(ROT_SPEED);
	oldPlaneX = game->player.camera.PlaneX;
	game->player.camera.PlaneX = game->player.camera.PlaneX * cos(ROT_SPEED) - game->player.camera.PlaneY * sin(ROT_SPEED);
	game->player.camera.PlaneY = oldPlaneX * sin(ROT_SPEED) + game->player.camera.PlaneY * cos(ROT_SPEED);
	return (1);
}