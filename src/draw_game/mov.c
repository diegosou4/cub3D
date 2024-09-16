
#include "../../includes/cub3D.h"


int player_mov(t_game *game, int keycode)
{
    if(keycode == KEY_W || keycode == KEY_S)
        return(key_ws(game,keycode));
    else if(keycode == KEY_D || keycode == KEY_A)
        return(key_da(game,keycode));
    else if(keycode == L_AR)
        return(key_l(game,keycode));
    else if(keycode == R_AR)
        return(key_r(game,keycode));
}

int key_ws(t_game *game, int keycode)
{
        if(keycode == KEY_S)
             game->player.PosY =  (game->player.Py + TAM_P) / TAM_Y_P;
        else
		    game->player.PosY =  (game->player.Py - TAM_P) / TAM_Y_P;
    	if(game->map[game->player.PosY][game->player.PosX] == '1')
		{
			game->player.PosY =  game->player.Py / TAM_Y_P;
			return (0);
		}
        if(keycode == KEY_S)
            game->player.Py += TAM_P;
        else
            game->player.Py -= TAM_P;
        draw_map(game,1);
        test_player(game,0xcb1313);
        draw_allray(game);
		mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
        return(1);
}


int key_da(t_game *game, int keycode)
{
        if(keycode == KEY_D)
            game->player.PosX = (game->player.Px + TAM_P) / TAM_X_P;
        else
            game->player.PosX = (game->player.Px - TAM_P) / TAM_X_P;
    	if(game->map[game->player.PosY][game->player.PosX] == '1')
        {
            game->player.PosX = game->player.Px / TAM_X_P;
            return (0);
        }
        if (keycode == KEY_D)
            game->player.Px += TAM_P;
        else
            game->player.Px -= TAM_P;
        draw_map(game,1);
        test_player(game,0xcb1313);
        draw_allray(game);
        mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
        return(1);
}

int key_l(t_game *game, int keycode)
{
    	draw_map(game,1);
		game->player.direction += 1;
		if(game->player.direction > 360)
			game->player.direction = 0;
		test_player(game,0xcb1313);
        draw_allray(game);
		mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
}
int key_r(t_game *game, int keycode)
{
    	draw_map(game,1);
        game->player.direction -= 1;
        if(game->player.direction < 0)
            game->player.direction = 360;
        test_player(game,0xcb1313);
        draw_allray(game);
        mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
}