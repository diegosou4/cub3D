/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:52:41 by diegmore          #+#    #+#             */
/*   Updated: 2024/11/21 17:44:39 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "macros.h"
# include "time.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
	int			status;
}				t_img;

typedef struct s_minimap
{
	int			*x_vals;
	int			*y_vals;
}				t_minimap;

typedef struct s_texture
{
	t_img		texture;
	bool		filled;
	int			duplicate;
}				t_texture;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	bool		filled;
	int			duplicate;
}				t_color;

typedef struct s_camera
{
	double		planex;
	double		planey;
}				t_camera;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_distx;
	double		side_disty;
	double		delta_distx;
	double		delta_disty;
	double		perpwalldist;
	double		currentrayx;
	double		lineheight;
	double		drawstart;
	double		drawend;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;

}				t_ray;

typedef struct s_map
{
	char		**data;
	int			width;
	int			height;
}				t_map;

typedef struct s_enemy
{
	double		x;
	double		y;
}				t_enemy;

typedef struct s_player
{
	t_ray		ray;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		direction;
	double		deltax;
	double		deltay;
	double		step;
	double		fade_factor;
	int			sprite_num;
	int			curr_frame;
	t_camera	camera;
	int			py;
	int			px;
	int			pa;
}				t_player;

typedef struct s_draw_x
{
	double		invdet;
	double		transformx;
	double		transformy;
	double		frequency;
	double		amplitude;
	double		horizontal_offset;
	double		enemyx;
	double		enemyy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
	int			stripe;
	int			tex_x;
	int			y;
	int			d;
	int			tex_y;
	int			color;
	int			i;
}				t_draw_x;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		canva;
	t_player	player;
	t_texture	texture[16];
	t_color		color[2];
	bool		hit_door;
	bool		light_on;
	bool		split_parse;
	bool		hit_enemy;
	bool		inside_wall;
	bool		changed_world;
	int			current_world;
	char		**map_info;
	char		**map;
	char		**ff_map;
	char		*line;
	char		*playcmd;
	char		*playbur;
	int			framectd;
	int			curr_map;
	int			current_img;
	int			status_free;
	int			x_mouse;
	int			y_mouse;
	int			x_mov;
	int			y_mov;
	int			n;
	int			e;
	int			o;
	int			s;
	int			num_enemies;
	int			rot_right;
	int			rot_left;
	t_enemy		enemies[MAX_ENEMIES];
	t_draw_x	draw;

}				t_game;

typedef void	(*t_draw_func)(t_game *game, t_img *texture, double angle);
typedef void	(*t_case_line_func)(t_game *game, char *line, char **split);

// Libft

void			*ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *src);
int				ft_is_space(char c);
char			**ft_split(char const *s, char c);
int				len_darray(char **arr);
bool			ft_whitespaces(char *str);
bool			ft_whitespace(char c);
int				ft_atoi(const char *str);
void			ft_freedarray(char **line);
int				ft_isdigit(int c);
int				ft_dstrlen(char **str);
char			**ft_dstrdup(char **src);
int				ft_strrchr(const char *str, int c);

// GNL
char			*get_next_line(int fd);
int				ft_strlen(char *str);
char			*ft_strchr(char *s, int c);
char			*ft_join(char *new_str, char *str, char *buffer);
char			*ft_strjoin(char *str, char *buffer);
char			*ft_rnewline(char *str);

// Parse

void			check_line(t_game *game);
char			*open_file(char *path);
int				check_ext(char *pathname, char *format, char *type);
void			init_parse(char *path);
char			*open_read(int fd);
void			ftjoinmap2(char *str, char *buffer, char *new_str);
char			*ftjoinmap(char *str, char *buffer);
char			*joinmap(char *new_str, char *buffer);
int				valid_line(char *line);
bool			all_num(char **split2);
int				save_direction(t_game *game, int c_col, int c_row);
void			fill_rgb(t_game *game,char **split, int index);
bool			flood_cases(t_game *game, int c_col, int c_row);
bool			is_wall(t_game *game, int c_col, int c_row);
bool			flood_fill(t_game *game, int c_col, int c_row);
void			check_hole(t_game *game, int end);
bool			filled_textures(t_game *game);
bool			filled_colors(t_game *game);
void			check_texture(t_game *game);
int				count_x(t_game *game);
void			check_map(t_game *game, int start);
void			check_first(t_game *game, char *line);
int				sizemap(t_game *game);
void			check_fl(t_game *game, int start, int end);
int				end_map(char *line_map);
void			check_middle(t_game *game, int end);
void			case_text(t_game *game, char *line, char **split);
void			case_addtex(t_game *game, char *line, char **split);
void			case_color(t_game *game, char *line, char **split);
void			split_line(char *line, t_game *game, t_case_line_func l_func,
					int charl);
void			check_direction(t_game *game);

// Draw
void			swift_rgb(t_game *game, int color, double fade_factor, int y);
void			bu_timer(t_game *game);
void			init_enemies(t_game *game);
void			draw_aux1(t_game *game);
void			enemy_val_aux(t_game *game);
void			enemy_val_aux2(t_game *game);
void			draw_enemy(t_game *game);
void			draw_walls(t_game *game, t_img *texture, double angle);
void			draw_walls_fade(t_game *game, t_img *texture, double angle);
int				return_pos(t_game *game);
int				check_world(t_game *game, int pos);
void			draw_texture(t_game *game, double angle);
int				key_event(int keycode, t_game *game);
void			start_window(t_game *game);
void			save_msc(t_game *game);
void			ingame(t_game *game);
void			key_rot(t_game *game, int keycode);
void			key_ligths(t_game *game, int keycode);
void			key_direction(t_game *game, int keycode);
void			define_mov(t_game *game, int keycode);
int				key_drop(int keycode, t_game *game);
void			draw_flashlight(t_game *game);
int				cc_mmap(t_game *game, int map_x, int map_y, int color);
void			draw_minimap_background(t_game *game, int map_height,
					double start_map_x, double start_map_y);
void			draw_minimap(t_game *game);
int				mouse_track(int x, int y, t_game *game);
int				mouse_monitor(t_game *game, int keycode);
int				arrow_left(t_game *game);
int				arrow_right(t_game *game);
int				key_w(t_game *game);
int				key_s(t_game *game);
int				key_d(t_game *game);
int				key_a(t_game *game);
int				player_mov(t_game *game);
void			paintimage(t_game *game, t_texture *img, int sx, int sy);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
int				my_mlx_pixel_get(t_img *data, int x, int y);
void			cal_shadow(t_game *game);
int				check_door(t_game *game, int map_x, int map_y);
void			draw_allray(t_game *game);
void			calculate_ray(t_game *game, int map_x, int map_y);
void			calculate_distance(t_game *game);
void			hit_wall(t_game *game, int map_x, int map_y);
void			check_rays(t_game *game);
void			draw_ray(t_game *game, double angle);
void			init_values2(t_game *game);
void			init_values(t_game *game);
void			init_values3(t_game *game);
void			define_direction(t_game *game, char direction);
void			start_map2(t_game *game, int ftime, int i, int y);
void			start_map(t_game *game, int ftime);
int				hex_color(t_game *game, int pos);
void			draw_skyfloor(t_game *game, double angle, double x, int pos);
t_img			load_img(t_game *game, char *path);
void			load_wall(t_game *game);
void			aux_rotate(t_game *game);
void			draw_enemy_stripes(t_game *game);

// Garbage

void			clear_texture(t_game *game, int *status, t_img *texture);
void			free_walls(t_game *game);
void			free_ff_map(t_game *game);
void			free_map_info(t_game *game);
void			free_game(t_game *game);
void			free_texture(t_game *game);
void			free_map(t_game *game);
void			destroy_game(t_game *game);
void			garabe_collector(t_game *game);
void			print_free(t_game *game, char *errostr);

#endif
