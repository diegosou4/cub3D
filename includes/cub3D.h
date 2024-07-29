#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

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

typedef struct s_assets
{
    t_img img;
    char *relative_path;
    int img_width;
    int img_height;
}   t_assets;

typedef struct s_wall
{
	t_assets texture;
	bool filled;
}	t_wall;


typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;


typedef struct s_game
{	
	t_wall wall[4];
	t_color color[2];
	char **map;

}   t_game;

void init_parse(char *path);
char	*open_read(int fd);
int	namemap(char *pathname);

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
int valid_line(char *line);

#endif