#include "../../includes/cub3D.h"

void case_text(t_game *game, char *line, char **split)
{
    if (line[0] == 'N' && line[1] == 'O')
    {
        game->wall[0].texture.relative_path = ft_strdup(split[1]);
        game->wall[0].filled = true;
    }
    else if (line[0] == 'S' && line[1] == 'O')
    {
        game->wall[1].texture.relative_path = ft_strdup(split[1]);
        game->wall[1].filled = true;
    }
    else if (line[0] == 'W' && line[1] == 'E')
    {
        game->wall[2].texture.relative_path = ft_strdup(split[1]);
        game->wall[2].filled = true;
    }
    else if (line[0] == 'E' && line[1] == 'A')
    {
        game->wall[3].texture.relative_path = ft_strdup(split[1]);
        game->wall[3].filled = true;
    }
}

bool all_num(char **split2)
{
    int i;
    int num;
    
    i = 0;
    num = 0;
    while(i != 3)
    {
        int j = 0;
        if(ft_strlen(split2[i]) == 0 || ft_strlen(split2[i]) > 3)
            return (false);
        while(split2[i][j] != '\0')
        {
            num = ft_atoi(split2[i]);
            if (ft_isdigit(split2[i][j]) == 0 || num < 0 || num > 255)
                return (false);
            j++;
        }
        i++;
    }
    return(true);
}

void case_color(t_game *game, char *line, char **split)
{
    char **split2;

    split2 = ft_split(split[1], ',');
    if (len_darray(split2) != 3 || all_num(split2) == false)
    {
        ft_freedarray(split);
        ft_freedarray(split2);
        print_free(game, "Error when trying to parse the map");
    }
    if (line[0] == 'F')
    {
        game->color[F].r = ft_atoi(split2[0]);
        game->color[F].g = ft_atoi(split2[1]);
        game->color[F].b = ft_atoi(split2[2]);
        game->color[F].filled = true;
    }
    else if (line[0] == 'C')
    {
        game->color[C].r = ft_atoi(split2[0]);
        game->color[C].g = ft_atoi(split2[1]);
        game->color[C].b = ft_atoi(split2[2]);
        game->color[C].filled = true;
    }
    ft_freedarray(split2);
}

int valid_line(char *line)
{
    int i = 2;

    if (line[i] == ' ')
    {
        i++;
        while (line[i] != '\0')
        {
            if (line[i] == ' ')
                return (0);
            i++;
        }
    }
    return (1);
}

void split_line(char *line, t_game *game, t_case_line_func l_func, int charl)
{
    char **split;
    int len;

    split = ft_split(line, ' ');
    len = len_darray(split);
 
    if (len == 2)
    {
        if (ft_strlen(split[0]) == charl)
        {
            l_func(game, line, split);
        }
    }
    else if (ft_whitespaces(line) == false)
    {
        ft_freedarray(split);
        print_free(game, "Error when trying to parse the map");
    }
    ft_freedarray(split);
}

void check_direction(t_game *game)
{
    int i;
    int j;
    
    i = 0;

    while (game->map_info[i] != NULL && filled_textures(game) != true)
        split_line(game->map_info[i++], game, case_text,2);
    while (game->map_info[i] != NULL && filled_colors(game) != true)
        split_line(game->map_info[i++], game, case_color,1);
    check_texture(game); 
    while (ft_whitespaces(game->map_info[++i]) == true)
        ;
    game->map = ft_dstrdup(game->map_info + i);
    check_map(game, i);
    
}



// primeiro map[0] so pode ter 1 ou espaco
// depois na segunda verifiacao tenho que ver se map[1]
// e maior ou menos que o map[0] se ele for maior
// tenho salvar a posicao do primeiro 1 e ultimo do map[0]
// depois tenho que verificar sempre se o map[0] tem 1 ou espaco
// se ele tiver 1 e o map[1] tiver 0 ok, se ele tiver  ' ' e o map[1]
// nao tiver 1 ele nao ta fechado
//
