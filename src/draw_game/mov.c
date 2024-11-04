
#include "../../includes/cub3D.h"

int mouse_track(int x, int y, t_game *game)
{
	if (game->x_mouse == x && game->y_mouse == y)
		return (0);
	game->x_mouse = x;
	game->y_mouse = y;
	return (0);
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

	return 0;
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

	return 0;
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

	return 0;
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

	return (0);
}

int arrow_left(t_game *game)
{
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(-ROT_SPEED) - game->player.dirY * sin(-ROT_SPEED);
	game->player.dirY = oldDirX * sin(-ROT_SPEED) + game->player.dirY * cos(-ROT_SPEED);
	double oldPlaneX = game->player.camera.PlaneX;
	game->player.camera.PlaneX = game->player.camera.PlaneX * cos(-ROT_SPEED) - game->player.camera.PlaneY * sin(-ROT_SPEED);
	game->player.camera.PlaneY = oldPlaneX * sin(-ROT_SPEED) + game->player.camera.PlaneY * cos(-ROT_SPEED);
	return (1);
}

int arrow_right(t_game *game)
{
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(ROT_SPEED) - game->player.dirY * sin(ROT_SPEED);
	game->player.dirY = oldDirX * sin(ROT_SPEED) + game->player.dirY * cos(ROT_SPEED);
	double oldPlaneX = game->player.camera.PlaneX;
	game->player.camera.PlaneX = game->player.camera.PlaneX * cos(ROT_SPEED) - game->player.camera.PlaneY * sin(ROT_SPEED);
	game->player.camera.PlaneY = oldPlaneX * sin(ROT_SPEED) + game->player.camera.PlaneY * cos(ROT_SPEED);
	
	return (1);
}

/* int	key_pressing(t_game *game)
{
	if(game->y_mov == 1 && game->x_mov == 1)
	{
		key_w(game);
		key_d(game);
		return (0);
	}
	if(game->y_mov == 1 && game->x_mov == -1)
	{
		key_w(game);
		key_a(game);
		return (0);
	}
	if(game->y_mov == 1)
		key_w(game);
	if(game->y_mov == -1)
		key_s(game);
	if(game->x_mov == 1)
		key_d(game);
	if(game->x_mov == -1)
		key_a(game);
	return (0);
} */

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
			{
				arrow_right(game);
			}
			else if ( deltaX < 0 || game->rot_Left == 1)
			{
				arrow_left(game);
			}
			//draw_allray(game);
			prev_x_mouse = WIDTH /2;
			//mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		}
		player_mov2(keycode, game);
		//key_pressing(game);
		draw_allray(game);
		//draw_minimap(game);
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
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
	return (0);
}

int player_mov2(int keycode, t_game *game)
{
	int	x_mov;
	int	y_mov;

	y_mov = game->y_mov;
	x_mov = game->x_mov;
	// dprintf(2, "xmov %d\n", x_mov);
	// dprintf(2, "ymov %d\n", y_mov);
	// dprintf(2, "xmovGme %d\n", game->x_mov);
	// dprintf(2, "ymovGme %d\n", game->y_mov);
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
	game->x_mov = x_mov;
	game->y_mov = y_mov;
	return (0);
}






