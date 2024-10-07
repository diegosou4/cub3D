#ifndef CUB3D_H
#define CUB3D_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include "../minilibx-linux/mlx.h"


#include "macros.h"


typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*relative_path;
	int			img_width;
	int			tamsprite;
	int			img_height;
}				t_img;



typedef struct s_wall
{
	t_img texture;
	bool filled;
}	t_wall;


typedef struct s_color
{
	int r;
	int g;
	int b;
	bool filled;
}	t_color;


typedef struct s_camera
{
	double PlaneX;
	double PlaneY;
} t_camera;

typedef struct s_time
{
	double oldtime;
	double time;
	double frametime;

}	t_time;


typedef struct s_ray
{
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	double lineheight;
	double drawStart;
	double drawEnd;
} t_ray;



typedef struct s_player
{
	double PosX; // Posicao do player no mapa em x e y
	double PosY;
	t_ray ray;
	t_time time;
	double direction;
	double deltax;
	double deltay;
	t_camera camera;
	double dirX;
	double dirY;
	int Py; // Posicao em Pixel
	int Px; 
	int pa;
}	t_player;

typedef struct s_game
{	
	void		*mlx;
	void		*win;
	t_img		canva;
	t_player player;
	t_wall wall[4];
	t_color color[2];
	char **map_info;
	char **map;
	char **ff_map;
	char *line;
	int status_free;
}   t_game;



typedef void (*t_case_line_func)(t_game *game, char *line, char **split);

void init_parse(char *path);
char	*open_read(int fd);
int	check_ext(char *pathname, char *format, char *type);

//
void	ftjoinmap2(char *str, char *buffer, char *new_str);
char	*ftjoinmap(char *str, char *buffer);
char	*joinmap(char *new_str, char *buffer);

// Libft
 
void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *src);
int ft_is_space(char c);
char	**ft_split(char const *s, char c);
int	len_darray(char **arr);
bool ft_whitespaces(char *str);
bool ft_whitespace(char c);
int	ft_atoi(const char *str);
void	ft_freedarray(char **line);
int	ft_isdigit(int c);
int ft_dstrlen(char **str);
char **ft_dstrdup(char **src);
int	ft_strrchr(const char *str, int c);

// GNL
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_join(char *new_str, char *str, char *buffer);
char	*ft_strjoin(char *str, char *buffer);
char	*ft_rnewline(char *str);



// Parse Map
void check_direction(t_game *game);
bool filled_textures(t_game *game);
bool filled_colors(t_game *game);
int valid_line(char *line);
void check_texture(t_game *game);
void check_map(t_game *game, int start);
bool flood_fill(t_game *game, int c_col, int c_row);
// Draw Game
void draw(int x,int y, int color, t_game *game);
void draw_minimap(t_game *game);
void start_window(t_game *game);
void load_wall(t_game *game);
t_img	load_img(t_game *game, int texture);
int	my_mlx_pixel_get(t_img *data, int x, int y);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
// void draw_ray(t_game *game, double angle);
void draw_map(t_game *game, int ftime);
void test_player(t_game *game, int color);
void draw_allray(t_game *game);
void raycasting(t_game *game);
void draw_ray(t_game *game, double angle);
// Moviment

int player_mov(t_game *game, int keycode);
int key_da(t_game *game, int keycode);
int key_ws(t_game *game, int keycode);
int key_l(t_game *game, int keycode);
int key_r(t_game *game, int keycode);
// Garabe Collector
void garabe_collector(t_game *game);
void print_free(t_game *game, char *errostr);
void free_map_info(t_game *game);
void free_ff_map(t_game *game);
void free_walls(t_game *game, int texture);
void destroy_game(t_game *game);
void clear_screen(t_game *game);
void define_direction(t_game *game , char direction);
#endif