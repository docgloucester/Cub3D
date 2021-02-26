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
# define PI						3.141592654
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17
# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>

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
#  define UP_KEY 119
#  define DOWN_KEY 115
#  define LEFT_KEY 97
#  define RIGHT_KEY 100
#  define DPAD_LEFT 65361
#  define DPAD_RIGHT 65363
# endif

typedef struct	s_point
{
	float	x;
	float	y;
}				t_point;

typedef struct	s_coord
{
	int	x;
	int	y;
	int	count;
}				t_coord;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_texture
{
	t_img	img;
}				t_texture;

typedef struct	s_sprite
{
	float			norm;
	float			angle;
	t_point			coord;
	int				is_hor;
	struct s_sprite	*next;
}				t_sprite;

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
	int		map_x;
	int		map_y;
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

typedef struct	s_keys
{
	int	x;
	int	y;
	int	rot;
}				t_keys;

typedef	struct	s_vars {
	void		*mlx;
	void		*win;
	float		*norms;
	t_params	params;
	t_player	player;
	t_keys		move;
	t_img		img;
	t_img		player_img;
	t_img		fps_img;
	t_texture	n_text;
	t_texture	s_text;
	t_texture	e_text;
	t_texture	w_text;
	t_texture	sprite;
}				t_vars;

t_params		parse_file(char *path);
void			free_split(char **split);
float			float_modulo(float a, float b);
void			my_pixelput(t_img *img, int x, int y, int col);
unsigned int	get_pixel(t_img *img, int x, int y);
void			draw_line(t_vars *mywin, t_point start, t_point end, int col);
void			draw_square(t_img *img, int x, int y, int px, int col);
void			draw_rect(t_img *img, t_point start, int width, int h, int col);
void			draw_stripe(t_vars *mywin, int x_start, float norm,
				t_texture *text, float offset);
void			draw_sprite(t_vars *mywin, int x, int height, float offset);
void			fill_window(t_vars *mywin, t_img *img, int col);
void			mlx_merge_img(t_vars *mw, t_img *tmp, t_img *bck, t_img *front);
void			change_angle(t_player *player, float angle);
void			deal_map(t_params *params, char	**line, int fd);
int				get_square_side(t_vars *mywin);
float			get_norm(t_point start, t_point end);
int				cmp_norm(t_point start, t_point end0, t_point end1);
void			build_image(t_vars *mywin, t_img *img);
void			place_player(t_vars *mywin, int col);
void			draw_player_dir(t_vars *mywin, int col);
void			draw_rays(t_vars *mywin);
void			addsprite(t_sprite **spr, t_point crd, float norm, float diff);
void			display_sprites(t_vars *mywin, t_sprite *sprites);
void			freesprite(t_sprite *sprites);
void			create_bmp(char *image, int height, int width);
void			check_error(t_vars *mywin);

#endif
