/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:09:58 by diegmore          #+#    #+#             */
/*   Updated: 2024/12/03 11:58:58 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define M_PI 3.14159265358979323846

# define ESC 65307
# define KEY_D 100
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_F 102
# define KEY_F 102
# define L_AR 65361
# define R_AR 65363
# define MOVE_SPEED 0.03
# define MIN_PROXIMITY_DISTANCE 0.4
# define ROT_SPEED 0.04

# define NUM_TEXTURE 16
# define MAX_ENEMIES 100
# define MAX_DOORS 10

# define FOV 66

# define BLUE 0x0000FF
# define RED 0xFF0000
# define GRAY_COLOR 0x808080
# define SKY_COLOR 1
# define FLOOR_COLOR 2
# define RGB_PURPLE 0x800080
# define RBG_RED 0xFF0000
# define RBG_GREEN 0x00FF00
# define RBG_BLUE 0x0000FF
# define RBG_WHITE 0xFFFFFF
# define RBG_BLACK 0x000000
# define RBG_YELLOW 0xFFFF00
# define BACK_YELLOW 0xA5A51C
# define TETO 0x780606
# define FLOOR 0xbdb76b
# define FLOOR_MAP 0xaeac5c
# define BLOOD_RED 0x780606
# define TRANSPARENT_COLOR 0xfff000

# define WIDTH 1080
# define HEIGHT 720
# define TAM_TEXT 256
# define TAM_Y_P 32
# define TAM_X_P 32
# define TAM_P 32
# define MINIMAP_WIDTH 130
# define MINIMAP_HEIGHT 130
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
//
# define MINIMAP_SIZE 200     // Tamanho do minimap quadrado
# define MINIMAP_SCALE 0.9    // Fator de escala pro mapa
# define PLAYER_MARKER_SIZE 4 // Tamanho do player sprite
# define MINIMAP_MARGIN 20    // margem da janela da window
# define TILE_SIZE 10         // tamanho de cada quadricula
# define MAX_RENDER_DISTANCE 3.0

# define A_NORTH 270
# define A_SOUTH 90
# define A_WEST 180
# define A_EAST 0

//	Frente + 1y
//	Tras   - 1y
//	Direita + 1x
//	Esquerda - 1x

enum	e_dirtype
{
	IDL,
	MOV_N,
	MOV_S,
	MOV_E,
	MOV_O,
	RIGHT_SPN,
	LEFT_SPN,
};

enum	e_rbgtexture
{
	F,
	C
};

enum	e_option
{
	PARSE,
	FINAL,
	FLOOD,
	MLX
};

enum	e_adicionaltextures
{
	PLAYER = 12,
	OBJECT = 13,
	DOOR = 14
};

#endif
