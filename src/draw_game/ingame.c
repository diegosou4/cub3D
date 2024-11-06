#include "../../includes/cub3D.h"


void ingame(t_game *game)
{
    const char *playCommand = "paplay assets/music/liminal.wav > /dev/null 2>&1 &";
	start_map(game,0);
	
	// printf_debug(game);
	draw_allray(game);

	// system(playCommand);
	//draw_minimap(game);   //verifica a posição do rato na janela
	mlx_hook(game->win, 2, (1L << 0), key_event, game);
	mlx_hook(game->win, 3, (1L << 1), key_drop, game);
	mlx_hook(game->win, 6, (1L << 6), mouse_track, game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_loop_hook(game->mlx, mouse_monitor, game);	//consoante a mudança de posição ela executa um movimento
	mlx_loop(game->mlx);
}
