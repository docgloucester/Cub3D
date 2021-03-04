/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:41:53 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/04 13:42:17 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void			draw_line(t_vars *mywin, t_point start, t_point end, int col)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = (int)fabs(end.x - start.x);
	sx = start.x < end.x ? 1 : -1;
	dy = -(int)fabs(end.y - start.y);
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

void			draw_stripe(t_vars *mywin, int x_start, float norm, t_img *text, float offset)
{
	int		y;
	int		y_start;
	int		col;
	int		height;

	height = get_square_side(mywin) * mywin->params.res_y / norm;
	y_start = (mywin->params.res_y - height) / 2;
	y = -1;
	while (++y < height)
	{
		if (y_start + y >= 0 && y_start + y < mywin->params.res_y)
		{
			col = get_pixel(text, text->width - 1 - (int)(offset * (float)text->width), (int)((float)y / (float)height * (float)text->height));
			if (col << 8 != 0)
				my_pixelput(&mywin->fps_img, x_start, y_start + y, col);
		}
	}
}

void			mlx_merge_img(t_vars *mywin, t_img *temp_img, t_img *back, t_img *front)
{
	int	x;
	int	y;
	int	col;

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
