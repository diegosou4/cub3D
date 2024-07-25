#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
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

#endif