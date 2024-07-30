#include "../../includes/cub3D.h"


//  I need fix this function
// to adpat to the new struct

// t_img	load_img(int texture, t_game *game)
// {
// 	t_img	img;

// 	img.relative_path = game->wall[texture].texture.relative_path;
// 	img.img = mlx_xpm_file_to_image(game->mlx, img.relative_path,
// 			&img.img_width, &img.img_height);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 			&img.endian);
// 	return (img);
// }