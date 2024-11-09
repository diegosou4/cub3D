

#include "../../includes/cub3D.h"


static void key_rot(t_game *game, int keycode)
{
	if (keycode == L_AR)
		game->rot_Left = 1;
	else if (keycode == R_AR)
		game->rot_Right = 1;
}

static void key_ligths(t_game *game, int keycode)
{
	if (keycode == KEY_F)
	{
		if (game->light_on == 0)
			game->light_on = 1;
		else 
			game->light_on = 0;
	}
}

static void key_direction(t_game *game, int keycode)
{
    if (keycode == KEY_A)
	{
		game->x_mov -= 1;
		game->O = 1;
	}	
	else if (keycode == KEY_D)
	{
		game->x_mov += 1;
		game->E = 1;
	}	
	else if (keycode == KEY_W)
	{
		game->y_mov -= 1;
		game->N = 1;
	}
	else if (keycode == KEY_S)
	{
		game->y_mov += 1;
		game->S = 1;
	}
}

void	define_mov(t_game *game, int keycode)
{
    key_rot(game, keycode);
    key_ligths(game, keycode);
    key_direction(game, keycode);
}



int	key_drop(int keycode, t_game *game)
{
	if (keycode == KEY_W && (game->y_mov == 0 || game->y_mov == -1))
	{
		//game->light_on = 0;
		game->y_mov += 1;
		game->N = 0;
	}	
	if (keycode == KEY_S && (game->y_mov == 0 || game->y_mov == 1))
	{
		//game->light_on = 0;
		game->y_mov -= 1;
		game->S = 0;
	}
	if (keycode == KEY_A && (game->x_mov == 0 || game->x_mov == -1))
	{
		//game->light_on = 0;
		game->x_mov += 1;
		game->O = 0;
	}
	if (keycode == KEY_D && (game->x_mov == 0 || game->x_mov == 1)) 
	{
		//game->light_on = 0;
		game->x_mov -= 1;
		game->E = 0;
	}
	if ((game->rot_Left == 1 && keycode == L_AR) || (game->rot_Right == 1 && keycode == R_AR))
    {
        game->rot_Left = 0;
        game->rot_Right = 0;
    }
	return (0);
}
