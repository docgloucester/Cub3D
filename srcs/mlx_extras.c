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

void			change_angle(t_player *player, float angle)
{
	while (angle <= 0)
		angle += 2 * PI;
	while (angle > 2 * PI)
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

void			draw_block(t_vars *mywin, int x_start, t_point dims, t_texture *text)
{
	int	x;
	int	y;
	int	y_start;
	int	col;

	y_start = (mywin->params.res_y - dims.y) / 2;
	y = -1;
	while (++y < dims.y)
	{
		x = -1;
		while (++x < dims.x)
		{
			if (y_start + y >= 0 && y_start + y < mywin->params.res_y && x_start + x >= 0 && x_start + x < mywin->params.res_x)
			{
				col = get_pixel(&text->img, text->img.width - 1 - text->i, (int)((float)y / dims.y * (float)text->img.height));
				my_pixelput(&mywin->fps_img, x_start + x, y_start + y, col);
			}
		}
	}
	text->i++;
	if (text->i >= text->img.width)
		text->i = 0;
}

void			draw_sprite(t_vars *mywin, int x_start, t_point dims, t_texture *text)
{
	int	x;
	int	y;
	int	y_start;
	int	col;

	y_start = (mywin->params.res_y - dims.y) / 2;
	y = -1;
	while (++y < dims.y)
	{
		x = -1;
		while (++x < dims.x)
		{
			if (y_start + y >= 0 && y_start + y < mywin->params.res_y && x_start + x >= 0 && x_start + x < mywin->params.res_x)
			{
				col = get_pixel(&text->img, text->img.width - 1 - text->i, (int)((float)y / dims.y * (float)text->img.height));
				if ((col & (0xFF << 24)) != (int)0xFF000000)
					my_pixelput(&mywin->fps_img, x_start + x, y_start + y, col);
			}
		}
	}
	text->i++;
	if (text->i >= text->img.width)
		text->i = 0;
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

void		draw_rect(t_img *img, t_point start, int width, int height, int col)
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

float			getNorm(t_point start, t_point end)
{
	return (sqrtf((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y)));
}

int			cmpNorm(t_point start, t_point end0, t_point end1)
{
	float	norm1;
	float	norm0;

	norm1 = getNorm(start, end1);
	norm0 = getNorm(start, end0);
	if (norm1 < norm0)
		return (1);
	return (- 1);
}
