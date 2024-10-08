#ifndef MACROS_H
#define MACROS_H




#define M_PI 3.14159265358979323846

# define ESC 65307
# define KEY_D 100
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define L_AR 65361
# define R_AR 65363
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1


# define FOV 66

#define BLUE 0x0000FF
#define RED 0xFF0000
#define GRAY_COLOR 0x808080
#define SKY_COLOR 0x87CEEB
#define  RBG_RED 0xFF0000
#define RBG_GREEN 0x00FF00
#define RBG_BLUE 0x0000FF
#define RBG_WHITE 0xFFFFFF
#define RBG_BLACK 0x000000
#define RBG_YELLOW 0xFFFF00

#define WIDTH 1280
#define HEIGHT 640

#define TAM_Y_P 32
#define TAM_X_P 32
#define TAM_P  8


#define A_NORTH 270
#define A_SOUTH 90
#define A_WEST 180
#define A_EAST 0

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

#endif