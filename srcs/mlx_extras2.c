/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_extras2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:55:25 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/05 13:55:47 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	mlx_merge_img(t_vars *mywin, t_img *temp_img, t_img *back, t_img *front)
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
			col = get_pixel(front, 4 * x, 4 * y) == 0xFFFFFFFF ?
			get_pixel(back, 4 * x, 4 * y) : get_pixel(front, 4 * x, 4 * y);
			my_pixelput(temp_img, x, y, col);
		}
	}
}
