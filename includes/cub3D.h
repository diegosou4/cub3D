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
	int         status;
}				t_img;

typedef struct s_minimap
{
	int			*x_vals;
	int			*y_vals;
}	t_minimap;


typedef struct s_texture
{
	t_img texture;
	bool filled;
}	t_texture;


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


typedef struct s_ray
{
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	double currentRayX;
	double lineheight;
	double drawStart;
	double drawEnd;
	int stepX;
	int stepY;
	int hit;
	int side;
	
} t_ray;

typedef struct s_map
{
	char	**data;
	int	width;
	int	height;
}	t_map;

typedef struct s_player
{
	t_ray ray;
	double PosX; 
	double PosY;
	double dirX;
	double dirY;
	double direction;
	double deltax;
	double deltay;
	int		sprite_num;
	int		curr_frame;
	t_camera camera;
	int Py; 
	int Px; 
	int pa;
}	t_player;

typedef struct s_game
{	
	void	*mlx;
	void	*win;
	t_img	canva;
	t_player	player;
	t_texture texture[15];
	t_color	color[2];
	bool	hit_door;
	bool	light_on;
	bool	split_parse;
	char	**map_info;
	char	**map;
	char	**ff_map;
	char	*line;
	int		frameCtd;
	int		curr_map;
	int		current_img;
	int		status_free;
	int		x_mouse;
	int		y_mouse;
	int		x_mov;
	int		y_mov;
	int		N;
	int		E;
	int		O;
	int		S;
	int 	rot_Left;
	int 	rot_Right;
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
void start_window(t_game *game);
void load_wall(t_game *game);
t_img	load_img(t_game *game, char *path);
int	my_mlx_pixel_get(t_img *data, int x, int y);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int hex_color(t_game *game, int pos);
void draw_skyfloor(t_game *game,double angle,double x, int pos);
void draw_minimap(t_game *game);
void draw_flashlight(t_game *game);
// void draw_ray(t_game *game, double angle);
void start_map(t_game *game, int ftime);
void paintimage(t_game *game, t_img *img, int sx, int sy);
void draw_allray(t_game *game);
void draw_ray(t_game *game, double angle);
void ingame(t_game *game);

// Moviment
void	define_mov(t_game *game, int keycode);
int		key_event(int keycode, t_game *game);
int		key_drop(int keycode, t_game *game);
int		mouse_track(int x, int y, t_game *game);
int		mouse_monitor(t_game *game, int keycode);
int		player_mov(t_game *game);
void  	init_values(t_game *game);
void	draw_texture(t_game *game, double angle);
// Garabe Collector
void	garabe_collector(t_game *game);
void	free_game(t_game *game);
void	print_free(t_game *game, char *errostr);
void	free_map_info(t_game *game);
void	free_ff_map(t_game *game);
void	free_walls(t_game *game);
void	destroy_game(t_game *game);
void	define_direction(t_game *game , char direction);
#endif