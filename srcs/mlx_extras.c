/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_extras.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 02:47:51 by rgilles           #+#    #+#             */
/*   Updated: 2020/08/26 02:47:53 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float			float_modulo(float a, float b)
{
	while (a >= b)
		a -= b;
	return a;
}
void			change_angle(t_player *player, float angle)
{
	while (angle < - PI)
		angle += 2 * PI;
	while (angle >= PI)
		angle -= 2 * PI;
	player->angle = angle;
	player->dx = cosf(angle);
	player->dy = - sinf(angle);
}

void			my_pixelput(t_img *img, int x, int y, int col)
{
	*(int*)(img->addr + y * img->line_length + x
		* (img->bits_per_pixel / 8)) = col;
}

unsigned int	get_pixel(t_img *img, int x, int y)
{
	return(*(int*)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)));
}

void			fill_window(t_vars *mywin, t_img *img, int col)
{
	int 	x;
	int 	y;
	
	y = -1;
	while (++y < mywin->params.res_y)
	{
		x = -1;
		while (++x < mywin->params.res_x)
			my_pixelput(img, x, y, col);
	}
}

void			draw_line(t_vars *mywin, t_point start, t_point end, int col)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = (int)fabs(end.x - start.x);
	sx = start.x < end.x ? 1 : -1;
	dy = - (int)fabs(end.y - start.y);
	sy = start.y < end.y ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (start.x >= 0 && start.y >= 0 && start.x < mywin->params.res_x && start.y < mywin->params.res_y)
			my_pixelput(&mywin->player_img, (int)start.x, (int)start.y, col);
		if (2 * err >= dy)
		{
			if ((int)start.x == (int)end.x)
				break ;
			start.x += sx;
			if (2 * err <= dx)
			{
				if ((int)start.y == (int)end.y)
					break ;
				start.y += sy;
				err += dx;
			}
			err += dy;
		}
		else if (2 * err <= dx)
		{
			if ((int)start.y == (int)end.y)
				break ;
			start.y += sy;
			err += dx;
		}
	}
}

int				shade_color(int orig_col, float norm)
{
	int	r;
	int	g;
	int	b;

	r = 1 / norm * (orig_col & (0xFF << 16));
	g = 1 / norm * (orig_col & (0xFF << 8));
	b = 1 / norm * (orig_col & 0xFF);
	return (0x00 << 24 | r << 16 | g << 8 | b);
}

void			draw_stripe(t_vars *mywin, int x_start, float norm, t_texture *text, float offset)
{
	int		y;
	int		y_start;
	int		col;
	int 	height;

	height = get_square_side(mywin) * mywin->params.res_y / norm;
	y_start = (mywin->params.res_y - height) / 2;
	y = -1;
	while (++y < height)
	{
		if (y_start + y >= 0 && y_start + y < mywin->params.res_y)
		{
			col = get_pixel(&text->img, text->img.width - 1 - (int)(offset * (float)text->img.width), (int)((float)y / (float)height * (float)text->img.height));
			if (col << 8 != 0)
				my_pixelput(&mywin->fps_img, x_start, y_start + y, col);
		}
	}
}

void			draw_square(t_img *img, int x_start, int y_start, int side_length_px, int col)
{
	int	x;
	int	y;

	y = -1;
	while (++y < side_length_px)
	{
		x = -1;
		while (++x < side_length_px)
			my_pixelput(img, x_start + x, y_start + y, col);
	}
}

void			draw_rect(t_img *img, t_point start, int width, int height, int col)
{
	int	x;
	int	y;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			my_pixelput(img, start.x + x, start.y + y, col);
	}
}

void			mlx_merge_img(t_vars *mywin, t_img *temp_img, t_img *back, t_img *front)
{
	int 	x;
	int 	y;
	int 	col;
	
	y = -1;
	while (++y < mywin->params.res_y / 4)
	{
		x = -1;
		while (++x < mywin->params.res_x / 4)
		{
			col = get_pixel(front, 4 * x, 4 * y) == 0xFFFFFFFF ? get_pixel(back, 4 * x, 4 * y) : get_pixel(front, 4 * x, 4 * y);
			my_pixelput(temp_img, x, y, col);
		}
	}
}

float			get_norm(t_point start, t_point end)
{
	return (sqrtf(powf(start.x - end.x, 2) + powf((start.y - end.y), 2)));
}

int				cmp_norm(t_point start, t_point end0, t_point end1)
{
	float	norm1;
	float	norm0;

	if (end0.x == -1)
		return (1);
	if (end1.x == -1)
		return (0);
	norm1 = get_norm(start, end1);
	norm0 = get_norm(start, end0);
	if (norm1 < norm0)
		return (1);
	return (0);
}
