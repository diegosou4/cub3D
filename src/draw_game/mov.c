
#include "../../includes/cub3D.h"

int mouse_track(int x, int y, t_game *game)
{
	if (game->x_mouse == x && game->y_mouse == y)
		return (0);
	game->x_mouse = x;
	game->y_mouse = y;
	return (1);
}

int key_w(t_game *game) {
	// Calcula novas posições
	double newPosX = game->player.PosX + game->player.dirX * MOVE_SPEED;
	double newPosY = game->player.PosY + game->player.dirY * MOVE_SPEED;

	// Verifica se a nova posição não colide com uma parede
	if (game->map[(int)newPosY][(int)newPosX] != '1') {
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}

	return 1;
}

int key_s(t_game *game) {
	// Calcula novas posições para a movimentação para trás
	double newPosX = game->player.PosX - game->player.dirX * MOVE_SPEED;
	double newPosY = game->player.PosY - game->player.dirY * MOVE_SPEED;

	// Verifica se a nova posição não colide com uma parede
	if (game->map[(int)newPosY][(int)newPosX] != '1') {
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}

	return 1;
}

int key_d(t_game *game) {
	// Calcula novas posições para a movimentação à direita
	double newPosX = game->player.PosX + game->player.camera.PlaneX * MOVE_SPEED;
	double newPosY = game->player.PosY + game->player.camera.PlaneY * MOVE_SPEED;

	// Verifica se a nova posição não colide com uma parede
	if (game->map[(int)newPosY][(int)newPosX] != '1') {
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}

	return 1;
}


int key_a(t_game *game) {
	// Calcula novas posições para a movimentação à esquerda
	double newPosX = game->player.PosX - game->player.camera.PlaneX * MOVE_SPEED;
	double newPosY = game->player.PosY - game->player.camera.PlaneY * MOVE_SPEED;

	// Verifica se a nova posição não colide com uma parede
	if (game->map[(int)newPosY][(int)newPosX] != '1') {
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}

	return 1;
}

int arrow_left(t_game *game)
{
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(-ROT_SPEED) - game->player.dirY * sin(-ROT_SPEED);
	game->player.dirY = oldDirX * sin(-ROT_SPEED) + game->player.dirY * cos(-ROT_SPEED);
	double oldPlaneX = game->player.camera.PlaneX;
	game->player.camera.PlaneX = game->player.camera.PlaneX * cos(-ROT_SPEED) - game->player.camera.PlaneY * sin(-ROT_SPEED);
	game->player.camera.PlaneY = oldPlaneX * sin(-ROT_SPEED) + game->player.camera.PlaneY * cos(-ROT_SPEED);
	return 1;
}

int arrow_right(t_game *game)
{
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(ROT_SPEED) - game->player.dirY * sin(ROT_SPEED);
	game->player.dirY = oldDirX * sin(ROT_SPEED) + game->player.dirY * cos(ROT_SPEED);
	double oldPlaneX = game->player.camera.PlaneX;
	game->player.camera.PlaneX = game->player.camera.PlaneX * cos(ROT_SPEED) - game->player.camera.PlaneY * sin(ROT_SPEED);
	game->player.camera.PlaneY = oldPlaneX * sin(ROT_SPEED) + game->player.camera.PlaneY * cos(ROT_SPEED);
	
	return 1;
}

int mouse_monitor(t_game *game)
{
	static int	prev_x_mouse = WIDTH / 2;
	double		deltaX;

	deltaX = game->x_mouse - prev_x_mouse;
	if (game->x_mouse > 0 && game->x_mouse < WIDTH)
	{
		deltaX = game->x_mouse - prev_x_mouse;
		if (deltaX != 0)
		{
			if (deltaX > 0)
				arrow_right(game);
			else
				arrow_left(game);
			draw_allray(game);
			prev_x_mouse = game->x_mouse;
			//mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		}
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int player_mov(t_game *game, int keycode)
{
	if(keycode == KEY_W)
		return(key_w(game));
	else if(keycode == KEY_S)
		return(key_s(game));
	else if(keycode == KEY_D)
		return(key_d(game));
	else if(keycode == KEY_A)
		return(key_a(game));
	else if(keycode == L_AR)
		return(arrow_left(game));
	else if(keycode == R_AR)
		return(arrow_right(game));
	return (0);
}






