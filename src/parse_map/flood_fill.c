
#include "../../includes/cub3D.h"


int save_direction(t_game *game, int c_col,int c_row)
{
    if(ft_strrchr("NSWE", game->ff_map[c_col][c_row]) != 0)
    {       
        if(game->player.direction != -1)
        {
            printf("Invalid tem que tratar  isso\n");
            return (3);
        }
            
        game->player.x = c_col;
        game->player.y = c_row;
        game->player.direction = game->ff_map[c_col][c_row];
        game->ff_map[c_col][c_row] = 'x';
        return (1);
    }
    return (0);
}

bool flood_cases(t_game *game, int c_col, int c_row)
{
   
    if (c_col > 0 && flood_fill(game, c_col - 1, c_row) == false)
        return (false);
    if (c_col + 1 < len_darray(game->ff_map) && flood_fill(game, c_col + 1, c_row) == false)
        return (false);
    if (c_row > 0 && flood_fill(game, c_col, c_row - 1) == false)
        return (false);
    if (c_row + 1 < ft_strlen(game->ff_map[c_col]) && flood_fill(game, c_col, c_row + 1) == false)
        return (false);
 
    return (true);
}
bool is_wall(t_game *game, int c_col, int c_row)
{
    if(game->ff_map[c_col][c_row] == '1')
    {
        if(c_row < (ft_strlen(game->map[c_col]) - 1) 
        && ft_strchr("0NSWE",game->ff_map[c_col][c_row + 1]) != 0)
        {
             game->ff_map[c_col][c_row + 1] = '0';
            return(false);
        }  
    }
    if(game->ff_map[c_col][c_row] == '1')
        return (true);   
    return (false);
}

bool flood_fill(t_game *game, int c_col, int c_row)
{
    while(game->ff_map[c_col][c_row] != '\0')
    {
        if(is_wall(game,c_col,c_row) == true || game->ff_map[c_col][c_row] == 'x')
            return (true);
        if(save_direction(game, c_col, c_row) == 3)
            return (false); 
        if(game->ff_map[c_col][c_row] == '0')
        {
            game->ff_map[c_col][c_row] = 'x';
            if(flood_cases(game, c_col, c_row) == false)
                return(false); 
        }
        if(ft_strrchr("01x", game->ff_map[c_col][c_row]) == 0)
            return(false);
       c_row++;
    }

    return (true);
}
