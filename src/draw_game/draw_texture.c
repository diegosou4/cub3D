
#include "../../includes/cub3D.h"



void draw_minimap(t_game *game)
{
  int i;
  i = 0;


  while(game->map[i] != NULL)
  {
    int j = 0;
    while(game->map[i][j] != '\0')
    {
      if(game->map[i][j] == '1')
        draw(j * 10, i * 10, RBG_BLUE, game);
      else if(game->map[i][j] == '0')
        draw(j * 10, i * 10, RBG_WHITE, game);
        
      j++;
    }
    i++;
  }
    test_player(game, RBG_RED);
}