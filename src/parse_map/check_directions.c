
#include "../../includes/cub3D.h"




void case_line(t_game *game,char *line)
{
    printf("Line no case line %s \n",line);
    if(line[0] == 'N' && line[1] == 'O')
    {
        game->wall[0].texture.relative_path = ft_strdup(&line[3]);
        game->wall[0].filled = true;
    }
    if(line[0] == 'S' && line[1] == 'O')
    {
        game->wall[1].texture.relative_path = ft_strdup(&line[3]);
        game->wall[1].filled = true;
    }
    if(line[0] == 'W' && line[1] == 'E')
    {
        game->wall[2].texture.relative_path = ft_strdup(&line[3]);
        game->wall[2].filled = true;
    }
    if(line[0] == 'E' && line[1] == 'A')
    {
        game->wall[3].texture.relative_path = ft_strdup(&line[3]);
        game->wall[3].filled = true;
    }
}

// I need create a fuction to take the line
// and check if the line is a direction
// after this i will slipt the line 
// and check if the first and second is a direction
// and after space i have relative path and 
// need check if have more char after path 
// if have i will return error

int valid_line(char *line)
{
    int i;

    i = 2;

    if(line[i] == ' ')
    {
        i++;
        while(line[i] != '\0')
        {
            if(line[i] == ' ')
                return (0);
            i++;
        }
    }
    return(1);
}

void split_line(char *line, t_game *game)
{
    char **split;
    int len;

  
    split = ft_split(line, ' ');
    len = len_darray(split);
    if(len == 2)
    {
        if(ft_strlen(split[0]) == 2) 
            case_line(game,line);
    }
    else if(len > 2)
    {
        printf("Error\n");
    }else if(len == 1)
    {
        printf("Verificar se e spaces\n");
    }
    
}

void check_direction(t_game *game)
{
    int i;

    i = 0;

    while(game->map[i] != NULL && filled_textures(game) != true)
    {
        split_line(game->map[i],game);
        i++;
    }
    


}

