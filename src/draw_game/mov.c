
#include "../../includes/cub3D.h"



int key_w(t_game *game) {
    // Calcula novas posições
    float newPosX = game->player.PosX + game->player.dirX * MOVE_SPEED;
    float newPosY = game->player.PosY + game->player.dirY * MOVE_SPEED;

    // Verifica se a nova posição não colide com uma parede
    if (game->map[(int)newPosY][(int)newPosX] != '1') {
        game->player.PosX = newPosX;
        game->player.PosY = newPosY;
    }

    return 1;
}

int key_s(t_game *game) {
    // Calcula novas posições para a movimentação para trás
    float newPosX = game->player.PosX - game->player.dirX * MOVE_SPEED;
    float newPosY = game->player.PosY - game->player.dirY * MOVE_SPEED;

    // Verifica se a nova posição não colide com uma parede
    if (game->map[(int)newPosY][(int)newPosX] != '1') {
        game->player.PosX = newPosX;
        game->player.PosY = newPosY;
    }

    return 1;
}

int key_d(t_game *game) {
    // Calcula novas posições para a movimentação à direita
    float newPosX = game->player.PosX + game->player.dirY * MOVE_SPEED;  // Troca dirX e dirY para movimentação correta
    float newPosY = game->player.PosY - game->player.dirX * MOVE_SPEED;  // Troca dirX e dirY para movimentação correta

    // Verifica se a nova posição não colide com uma parede
    if (game->map[(int)newPosY][(int)newPosX] != '1') {
        game->player.PosX = newPosX;
        game->player.PosY = newPosY;
    }

    return 1;
}

int key_a(t_game *game) {
    // Calcula novas posições para a movimentação à esquerda
    float newPosX = game->player.PosX - game->player.dirY * MOVE_SPEED;  // Troca dirX e dirY para movimentação correta
    float newPosY = game->player.PosY + game->player.dirX * MOVE_SPEED;  // Troca dirX e dirY para movimentação correta

    // Verifica se a nova posição não colide com uma parede
    if (game->map[(int)newPosY][(int)newPosX] != '1') {
        game->player.PosX = newPosX;
        game->player.PosY = newPosY;
    }

    return 1;
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
}






