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
// The idea is salve the first time we find a 1  
// and the last time we find a 1 in first line
// and after we will check the map
// we will check if the map is surrounded by 1

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

void check_map(t_game *game, int start)
{
    int end;

   end = sizemap(game);
    check_fl(game, 0, end);
}