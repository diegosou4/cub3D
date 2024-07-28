
#include "../../includes/cub3D.h"


void whats_line(char *line, t_game *game)
{
    int i;
    int len;

    len = ft_strlen(line);
    i = 0;
    if(line[i] > 2)
    {
        while(line[i] != '\0')
        {
          
        }
    }
  
}

void case_line(t_game *game,char *line)
{
    if(line[0] == 'N' && line[1] == 'O')
    {
        game->wall[0].texture->relative_path = ft_strdup(&line[4]);
        game->wall[0].texture->img_width = 64;
        game->wall[0].texture->img_height = 64;
    }
    if(line[0] == 'S' && line[1] == 'O')
    {
        game->wall[1].texture.relative_path = ft_strdup(&line[4]);
        game->wall[1].texture.img_width = 64;
        game->wall[1].texture.img_height = 64;
    }
    if(line[0] == 'W' && line[1] == 'E')
    {
        game->wall[2].texture.relative_path = ft_strdup(&line[4]);
        game->wall[2].texture.img_width = 64;
        game->wall[2].texture.img_height = 64;
    }
    if(line[0] == 'E' && line[1] == 'A')
    {
        game->wall[3].texture.relative_path = ft_strdup(&line[4]);
        game->wall[3].texture.img_width = 64;
        game->wall[3].texture.img_height = 64;
    }
}

// I need create a fuction to take the line
// and check if the line is a direction
// after this i will slipt the line 
// and check if the first and second is a direction
// and after space i have relative path and 
// need check if have more char after path 
// if have i will return error

void check_direction(t_game *game)
{
    int i;

    i = 0;

    while(game->map[i])
    {
        
        i++;
    }


}

