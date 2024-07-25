#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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




void init_parse(char *path);
int open_file(char *path);
int	namemap(char *pathname);















// GNL
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_join(char *new_str, char *str, char *buffer);
char	*ft_strjoin(char *str, char *buffer);
char	*ft_rnewline(char *str);

#endif