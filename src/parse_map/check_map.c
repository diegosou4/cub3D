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

int sizemap(t_game *game,char **map, int i)
{
    while(map[i] != NULL && ft_whitespaces(map[i]) == false)
    {
        printf("Map[%d]: %s\n", i, map[i]);
        i++;
    }
    if(map[i] != NULL)
        print_free(game, "Invalid Map");
    return(i);
}

void check_map(t_game *game, int i)
{
    int j;
    int end;
    char *line;

    j = 0;    
    sizemap(game, game->map, i);
    // while(game->map[i] != NULL)
    // {
    //     line = game->map[i];
    //     end = ft_strlen(line);
        
    // }
    printf("Map is valid\n");
}