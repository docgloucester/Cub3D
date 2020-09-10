/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:37:37 by rgilles           #+#    #+#             */
/*   Updated: 2020/07/24 14:37:38 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.141592654
# include <libft.h>
# include <mlx.h>
# include <math.h>
#include <stdio.h>

# ifdef __APPLE__
#  define ESC_KEY 53
#  define UP_KEY 13
#  define DOWN_KEY 1
#  define LEFT_KEY 0
#  define RIGHT_KEY 2
#  define DPAD_LEFT 123
#  define DPAD_RIGHT 124
# elif defined __linux__
#  define ESC_KEY 65307
#  define UP_KEY 13
#  define DOWN_KEY 1
#  define LEFT_KEY 61
#  define RIGHT_KEY 64
#  define DPAD_LEFT 123
#  define DPAD_RIGHT 124
# endif

typedef struct	s_point
{
	float	x;
	float	y;
}				t_point;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef	struct	s_params
{
	int		res_x;
	int		res_y;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	char	*sp_path;
	int		floor_col;
	int		ceilg_col;
	char	**map;
	int		mapX;
	int		mapY;
	char	*err;
}				t_params;

typedef	struct	s_player
{
	float	x_pos;
	float	y_pos;
	float	angle;
	float	dx;
	float	dy;
}				t_player;

typedef	struct	s_vars {
	void		*mlx;
	void		*win;
	t_params	params;
	t_player	player;
	t_img		img;
}				t_vars;

t_params		parse_file(char *path);
void			free_split(char **split);
void			my_pixelput(t_img *img, int x, int y, int col);
void			draw_line(t_vars *mywin, t_point start, t_point end);
void			draw_square(t_img *img, int x_start, int y_start, int side_length_px, int col);
void			fill_window(t_vars *mywin, t_img *img, int col);
void			change_angle(t_player *player, float angle);
void			deal_map(t_params *params, char	**line, int fd);
void			build_image(t_vars *mywin, t_img *img);
void			place_player(t_vars *mywin, int col);

#endif
