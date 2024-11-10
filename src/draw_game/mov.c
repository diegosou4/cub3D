
#include "../../includes/cub3D.h"

int key_w(t_game *game) 
{
	double newPosX;
	double newPosY;

	newPosX = game->player.PosX + game->player.dirX * MOVE_SPEED;
	newPosY = game->player.PosY + game->player.dirY * MOVE_SPEED;
	if (game->map[(int)newPosY][(int)newPosX] != '1') 
	{
		game->player.PosX = newPosX;
		game->player.PosY = newPosY;
	}
	if(game->map[(int)newPosY][(int)newPosX] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
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
	if(game->map[(int)newPosY][(int)newPosX] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
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
	if(game->map[(int)newPosY][(int)newPosX] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
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
	if(game->map[(int)newPosY][(int)newPosX] == '2')
		game->inside_wall = true;
	else
		game->inside_wall = false;
	return (0);
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






