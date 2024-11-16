#include "../../includes/cub3D.h"

void init_enemies(t_game *game)
{
    int x;
    int y;

    y = 0;
    game->num_enemies = 0;
    while (game->map[y] != NULL)
    {
        x = 0;
        while (game->map[y][x] != '\0')
        {
            if (game->map[y][x] == '3' && game->num_enemies < MAX_ENEMIES)
            {
                game->enemies[game->num_enemies].x = x + 0.5; // Center in the cell
                game->enemies[game->num_enemies].y = y + 0.5; // Center in the cell
                game->num_enemies++;
            }
            x++;
        }
        y++;
    }
}

void draw_aux1(t_game *game)
{
    while (game->draw.y < game->draw.drawendy)
    {
        game->draw.d = (game->draw.y) * 256 - HEIGHT * 128 + game->draw.spriteheight * 128;
        game->draw.tex_y = ((game->draw.d * game->texture[15].texture.img_height) / game->draw.spriteheight) / 256;
        game->draw.color = my_mlx_pixel_get(&game->texture[15].texture,
                                            game->draw.tex_x, game->draw.tex_y);
        my_mlx_pixel_put(&game->canva, game->draw.stripe, game->draw.y,
                         game->draw.color);
        game->draw.y++;
    }
}

void enemy_val_aux(t_game *game)
{
    game->draw.invdet = 1.0 / (game->player.camera.planex * game->player.diry - game->player.dirx * game->player.camera.planey);
    game->draw.transformx = game->draw.invdet * (game->player.diry * game->draw.enemyx - game->player.dirx * game->draw.enemyy);
    game->draw.transformy = game->draw.invdet * (-game->player.camera.planey * game->draw.enemyx + game->player.camera.planex * game->draw.enemyy);
    game->draw.horizontal_offset = sin(game->framectd * game->draw.frequency) * game->draw.amplitude;
}

void enemy_val_aux2(t_game *game)
{
    game->draw.spritescreenx = (int)((WIDTH / 2) * (1 + game->draw.transformx / game->draw.transformy)) + (int)game->draw.horizontal_offset;
    game->draw.spriteheight = abs((int)(HEIGHT / game->draw.transformy));
    game->draw.drawstarty = -game->draw.spriteheight / 2 + HEIGHT / 2;
    if (game->draw.drawstarty < 0)
        game->draw.drawstarty = 0;
    game->draw.drawendy = game->draw.spriteheight / 2 + HEIGHT / 2;
    if (game->draw.drawendy >= HEIGHT)
        game->draw.drawendy = HEIGHT - 1;
    game->draw.spritewidth = abs((int)(HEIGHT / game->draw.transformy));
    game->draw.drawstartx = -game->draw.spritewidth / 2 + game->draw.spritescreenx;
    if (game->draw.drawstartx < 0)
        game->draw.drawstartx = 0;
    game->draw.drawendx = game->draw.spritewidth / 2 + game->draw.spritescreenx;
    if (game->draw.drawendx >= WIDTH)
        game->draw.drawendx = WIDTH - 1;
    game->draw.stripe = game->draw.drawstartx;
}

void draw_enemy(t_game *game)
{
    int i;
    double distance;

    i = -1;
    game->draw.frequency = 0.02;
    game->draw.amplitude = 10.0;
    while (++i < game->num_enemies)
    {
        game->draw.enemyx = game->enemies[i].x - game->player.posx;
        game->draw.enemyy = game->enemies[i].y - game->player.posy;
        distance = sqrt(game->draw.enemyx * game->draw.enemyx + game->draw.enemyy * game->draw.enemyy);
        if (distance < MIN_PROXIMITY_DISTANCE)
            continue;
        enemy_val_aux(game);
        if (game->draw.transformy > 0 && game->draw.transformy < game->player.ray.perpwalldist)
        {
            bu_timer(game);
            enemy_val_aux2(game);
            while (game->draw.stripe < game->draw.drawendx)
            {
                game->draw.tex_x = (int)((game->draw.stripe - (-game->draw.spritewidth / 2 + game->draw.spritescreenx)) * game->texture[15].texture.img_width / game->draw.spritewidth);
                if (game->draw.transformy > 0 && game->draw.stripe > 0 && game->draw.stripe < WIDTH && game->draw.transformy < game->player.ray.perpwalldist)
                {
                    game->draw.y = game->draw.drawstarty;
                    draw_aux1(game);
                }
                game->draw.stripe++;
            }
        }
    }
    game->framectd++;
}