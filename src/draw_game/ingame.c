#include "../../includes/cub3D.h"

int	key_drop(int keycode, t_game *game)
{
	if (keycode == KEY_W && (game->y_mov == 0 || game->y_mov == -1))
	{
		game->y_mov += 1;
		game->N = 0;
	}	
	if (keycode == KEY_S && (game->y_mov == 0 || game->y_mov == 1))
	{
		game->y_mov -= 1;
		game->S = 0;
	}
	if (keycode == KEY_A && (game->x_mov == 0 || game->x_mov == -1))
	{
		game->x_mov += 1;
		game->O = 0;
	}
	if (keycode == KEY_D && (game->x_mov == 0 || game->x_mov == 1)) 
	{
		game->x_mov -= 1;
		game->E = 0;
	}
	if (game->rot_Left == 1 && keycode == L_AR)
		game->rot_Left = 0;
	if (game->rot_Right == 1 && keycode == R_AR)
		game->rot_Right = 0;
	if (!game->S && !game->E && !game->N && !game->O)
		game->light_on = 0;
	return (0);
}


int	key_event(int keycode, t_game *game)
{
	
	mouse_monitor(game, keycode);
 	define_mov2(game, keycode);
	draw_allray(game); 
	if(keycode == ESC)
	{
		system("pkill aplay > /dev/null 2>&1");
		game->status_free = FINAL;
		
		mlx_do_key_autorepeaton(game->mlx);
		garabe_collector(game);
		destroy_game(game);
		exit(0);
	}
	if(game->map[(int)game->player.PosY][(int)game->player.PosX] == '1')
		printf("bateu\n");
	return (0);
}

void ingame(t_game *game)
{
    const char *playCommand = "paplay assets/music/Bessie_Coleman.wav > /dev/null 2>&1 &";
	draw_map(game,0);

	// printf_debug(game);
	draw_allray(game);
	system(playCommand);
	//draw_minimap(game);   //verifica a posição do rato na janela
	mlx_hook(game->win, 2, (1L << 0), key_event, game);
	mlx_hook(game->win, 3, (1L << 1), key_drop, game);
	mlx_hook(game->win, 6, (1L << 6), mouse_track, game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop_hook(game->mlx, mouse_monitor, game);	//consoante a mudança de posição ela executa um movimento
	mlx_loop(game->mlx);
}
