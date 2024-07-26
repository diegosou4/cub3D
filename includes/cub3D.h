#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


enum	direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
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
    int img_witdh;
    int img_height;
}   t_assets;

typedef struct s_wall
{
	t_assets *texture;
}	t_wall;

typedef struct s_game
{	
	t_wall wall[4];


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












// GNL
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_join(char *new_str, char *str, char *buffer);
char	*ft_strjoin(char *str, char *buffer);
char	*ft_rnewline(char *str);

#endif