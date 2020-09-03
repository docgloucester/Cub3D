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
