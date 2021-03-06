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
# define X_EVENT_EXIT			33
# include <libft.h>
# include <mlx.h>
# include <math.h>

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
	t_img		n_text;
	t_img		s_text;
	t_img		e_text;
	t_img		w_text;
	t_img		sprite;
	t_sprite	*sprites;
	int			i;
}				t_vars;

/*
** Events
*/
int				do_stuff(t_vars *mywin);
int				key_press(int keycode, t_vars *mywin);
int				key_release(int keycode, t_vars *mywin);
int				exit_hook(t_vars *mywin);

t_params		parse_file(char *path);

void			get_res(t_params *params, char *line);
int				get_col(t_params *params, char *line);
char			*get_path(t_params *params, char *line);
int				free_split(char **split);

void			dup_map(t_params *params, char	**line, int fd);
void			trim_map_y(t_params *params);
void			trim_map_x(t_params *params);

int				mk_bmp(char *image, int height, int width);
void			check_error(t_vars *mywin);
void			build_image(t_vars *mywin, t_img *img);
void			place_player(t_vars *mywin, int col);
void			draw_player_dir(t_vars *mywin, int col);
void			put_map(t_vars *mywin, t_img *img);

int				is_full_border(t_vars *mywin, t_coord curr, t_coord start,
					int prev);

/*
** Maths extras
*/
int				get_square_side(t_vars *mywin);
float			get_norm(t_vars *mywin, t_point end);
int				cmp_norm(t_vars *mywin, t_point end0, t_point end1);
void			chg_angle(t_player *player, float angle);
float			float_modulo(float a, float b);

/*
** Mlx extras
*/
void			my_pixelput(t_img *img, int x, int y, int col);
unsigned int	get_pixel(t_img *img, int x, int y);
void			fill_window(t_vars *mywin, t_img *img, int col);
void			mlx_merge_img(t_vars *mw, t_img *tmp, t_img *bck, t_img *front);
void			draw_square(t_img *img, t_point start, int px, int col);
void			draw_rect(t_vars *mywin, t_point start, int width, int h);
void			draw_line(t_vars *mywin, t_point end);

void			draw_rays(t_vars *mywin);
t_point			expand_ray(t_vars *mywin, t_point end, t_point delta_ray);

void			addsprite(t_vars *mywin, t_point crd, float norm, float diff);
void			display_sprites(t_vars *mywin);
void			freesprite(t_sprite *sprites);

void			put_blocks(t_vars *mywin, t_point v_end, t_point h_end,
				float diff);
void			draw_sprite(t_vars *mywin, int x, int height, float offset);
void			draw_stripe(t_vars *mywin, int x_start, t_point normoffset,
					t_img *text);
#endif
