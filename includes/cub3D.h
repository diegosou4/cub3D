#ifndef CUB3D_H
#define CUB3D_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

enum	direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum 	rbgtexture
{
	F,
	C
};

enum option
{
	PARSE,
	FINAL,
	FLOOD
};


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

typedef struct s_player
{
	int x;
	int y;
	int direction;
}	t_player;

typedef struct s_game
{	
	void		*mlx;
	void		*win;
	t_player player;
	t_wall wall[4];
	t_color color[2];
	char **map_info;
	char **map;
	char **ff_map;
	char *line;

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

// Garabe Collector
void garabe_collector(t_game *game, int option);
void print_free(t_game *game, char *errostr, int option);
void free_map_info(t_game *game);
#endif