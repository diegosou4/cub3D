#include "../../includes/cub3D.h"

void check_first(t_game *game, char *line)
{
    int i;

    i = 0;

    while(line[i] != '\0')
    {
        if(line[i] != '1' && line[i] != ' ')
            print_free(game, "Invalid Map");
        i++;
    }
}

int sizemap(t_game *game)
{
    int i;

    i = 0; 
    while(game->map[i] != NULL && ft_whitespaces(game->map[i]) == false)
        i++;
    if(game->map[i] != NULL)
        print_free(game, "Invalid Map");
    return(i);
}

void check_fl(t_game *game, int start, int end)
{
    int i;
    i = 0;
   
    while(game->map[start][i] != '\0')
    {
        if(game->map[start][i] != '1' && game->map[start][i] != ' ')
            print_free(game, "Invalid Map line start or end is inccorect");
        i++;
    }
    if(end == start)
        return;
    start += end - 1;
    end = start;
    check_fl(game, start, end);
}
int end_map(char *line_map)
{
    int i;
    int size_map;

    size_map = ft_strlen(line_map) - 1;
    while (size_map != 0)
    {
        while(ft_whitespace(line_map[size_map]) == true)
            size_map--;
        if(size_map == 0 || line_map[size_map] != '1')
            return(0);
        return(1);
    }
    return(0);
}
void check_middle(t_game *game, int end)
{
    int col;
    int row;

    row = 0;
    col = 1;
    game->ff_map = ft_dstrdup(game->map);
    game->status_free = FLOOD;
    while(game->map[col] != NULL && col < end)
    {
        while(game->map[col][row] != '\0')
        {
            row = 0;
            while(game->map[col][row] != '\0' && ft_whitespace(game->map[col][row]) == true)
                row++;
            if(row == ft_strlen(game->map[col]))
                print_free(game, "Invalid Map");
            if(game->map[col][row] != '1' || end_map(game->map[col]) == 0)
                print_free(game, "Invalid Map");
            if(flood_fill(game,col, row + 1) == false)
                print_free(game, "Invalid Map");
        break;
        }
        col++;
    }
    free_ff_map(game);
}

int count_x(t_game *game)
{  
    int row;
    int col;
    int x;
    x = 0;
    row = 0;
    col = 0;
    while(game->ff_map[col] != NULL)
    {
        while(game->ff_map[col][row] != '\0')
        {
            if(game->ff_map[col][row] == 'x')
                x++;
            row++;
        }
        row = 0;
        col++;
    }
    return(x);
}

void check_map(t_game *game, int start)
{
    int end;
    game->status_free = FINAL;
    end = sizemap(game);
    check_fl(game, 0, end);
    check_middle(game, end);
    if(count_x(game) == 1)
        print_free(game, "Invalid Map");
}