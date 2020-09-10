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

void	change_angle(t_player *player, float angle)
{
	while (angle <= 0)
		angle += 2 * PI;
	while (angle > 2 * PI)
		angle -= 2 * PI;
	player->angle = angle;
	player->dx = 10 * cosf(angle);
	player->dy = 10 * sinf(angle);
}

void	my_pixelput(t_img *img, int x, int y, int col)
{
	*(int*)(img->addr + y * img->line_length + x
		* (img->bits_per_pixel / 8)) = col;
}

void	fill_window(t_vars *mywin, t_img *img, int col)
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

// void	draw_line(t_img *img, t_point start, t_point end)
// {

// 	if abs(end.y - start.y) < abs(end.x - start.x)
// 	{
// 		if (start.x <= end.x)
// 			draw_lineN(img, start, end);
// 		else
// 			draw_lineN(img, start, end);
// 	}
// 	else
// 	{
// 		if (start.y <= end.y)
// 			draw_lineH(img, start, end);
// 		else
// 			draw_lineH(img, start, end);
// 	}
// }

void	draw_line(t_img *img, t_point start, t_point end)
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
	while (true)
	{
		plot(start.x, start.y);
		if (start.x == end.x && start.y == end.y)
			break;
		if (2 * err >= dy)
		{
			start.x += sx;
			if (2 * err <= dx)
			{
				start.y += sy;
				err += dx;
			}
			err += dy;
		}
		else if (2 * err <= dx)
		{
			start.y += sy;
			if (2 * err >= dy)
			{
				start.x += sx;
				err += dy;
			}
			err += dx;
		}
	}
}

void	draw_square(t_img *img, int x_start, int y_start, int side_length_px, int col)
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
