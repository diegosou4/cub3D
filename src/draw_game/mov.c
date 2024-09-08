
#include "../../includes/cub3D.h"


int player_mov(t_game *game, int keycode)
{
    if(keycode == KEY_W || keycode == KEY_S)
        return(key_ws(game,keycode));
    else if(keycode == KEY_D || keycode == KEY_A)
        return(key_da(game,keycode));

}

int key_ws(t_game *game, int keycode)
{
        if(keycode == KEY_S)
             game->player.ry =  (game->player.y + TAM_P) / TAM_Y_P;
        else
		    game->player.ry =  (game->player.y - TAM_P) / TAM_Y_P;
    	if(game->map[game->player.ry][game->player.rx] == '1')
		{
			game->player.ry =  game->player.y / TAM_Y_P;
			return (0);
		}
        if(keycode == KEY_S)
            game->player.y += TAM_P;
        else
            game->player.y -= TAM_P;
        draw_map(game,1);
        test_player(game,0xcb1313);
        draw_ray(game, game->player.angle);
		draw_ray(game, game->player.direction);
		mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
        return(1);
}


int key_da(t_game *game, int keycode)
{
        if(keycode == KEY_D)
            game->player.rx =  (game->player.x + TAM_P) / TAM_X_P;
        else
            game->player.rx =  (game->player.x - TAM_P) / TAM_X_P;
    	if(game->map[game->player.ry][game->player.rx] == '1')
        {
            game->player.rx =  game->player.x / TAM_X_P;
            return (0);
        }
        if (keycode == KEY_D)
            game->player.x += TAM_P;
        else
            game->player.x -= TAM_P;
        draw_map(game,1);
        test_player(game,0xcb1313);
        draw_ray(game, game->player.angle);
        draw_ray(game, game->player.direction);
        mlx_put_image_to_window(game->mlx, game->win, game->canva.img, 0, 0);
        return(1);
}

