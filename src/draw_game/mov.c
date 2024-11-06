
#include "../../includes/cub3D.h"

int mouse_track(int x, int y, t_game *game)
{
	if (game->x_mouse == x && game->y_mouse == y)
		return (0);
	game->x_mouse = x;
	game->y_mouse = y;
	return (0);
}

int key_w(t_game *game) 
{
	double newPosX;
	double newPosY;

	newPosX = game->player.PosX + game->player.dirX * MOVE_SPEED;
	newPosY = game->player.PosY + game->player.dirY * MOVE_SPEED;
	if (game->map[(int)newPosY][(int)newPosX] != '1') {
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}
	return 0;
}

int key_s(t_game *game) 
{
	double newPosX;
	double newPosY;

	newPosX = game->player.PosX - game->player.dirX * MOVE_SPEED;
	newPosY = game->player.PosY - game->player.dirY * MOVE_SPEED;
	if (game->map[(int)newPosY][(int)newPosX] != '1') 
	{
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}
	return 0;
}

int key_d(t_game *game)
{
	double newPosX;
	double newPosY;

	newPosX = newPosX = game->player.PosX + game->player.camera.PlaneX * MOVE_SPEED;
	newPosY = game->player.PosY + game->player.camera.PlaneY * MOVE_SPEED;
	if (game->map[(int)newPosY][(int)newPosX] != '1') 
	{
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}
	return 0;
}


int key_a(t_game *game) 
{
	double newPosX;
	double newPosY;

	newPosX = game->player.PosX - game->player.camera.PlaneX * MOVE_SPEED;
	newPosY = game->player.PosY - game->player.camera.PlaneY * MOVE_SPEED;
	if (game->map[(int)newPosY][(int)newPosX] != '1') 
	{
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}
	return (0);
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

int player_mov(t_game *game)
{
	if (game->N && game->y_mov == -1)
		key_w(game);
	if (game->S && game->y_mov == 1)
		key_s(game);
	if (game->E && game->x_mov == 1)
		key_d(game);
	if (game->O && game->x_mov == -1)
		key_a(game);
	if(game->rot_Left == 1)
		arrow_left(game);
	if(game->rot_Right == 1)
		arrow_right(game);
	return (0);
}






