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

    i = 0;

    while(i != 3)
    {
        int j = 0;
        while(split2[i][j] != '\0')
        {
            if (ft_isdigit(split2[i][j]) == 0)
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
        printf("Error\n");
        exit(0);
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
        printf("Error\n");
        exit(0);
    }
    ft_freedarray(split);
}

void check_direction(t_game *game)
{
    int i;

    i = 0;

    while (game->map[i] != NULL && filled_textures(game) != true)
    {
        split_line(game->map[i], game, case_text,2);
        i++;
    }
    printf("chega aqui\n");
    while (game->map[i] != NULL && filled_colors(game) != true)
    {
        split_line(game->map[i], game, case_color,1);
        i++;
    }
    printf(" Done \n");
}
