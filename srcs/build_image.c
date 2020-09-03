/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:34:42 by rgilles           #+#    #+#             */
/*   Updated: 2020/09/03 15:34:56 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		get_square_side(t_vars *mywin)
{
	int	useHeight;

	useHeight = 1;
	if (mywin->params.mapY < mywin->params.mapX)
		useHeight = 0;
	ft_printf("square side : %d\n", ((1 - useHeight) * mywin->params.res_x + (0 + useHeight) * mywin->params.res_y) / ((1 - useHeight) * mywin->params.mapX + (0 + useHeight) * mywin->params.mapY));
	return (((1 - useHeight) * mywin->params.res_x + (0 + useHeight) * mywin->params.res_y) / ((1 - useHeight) * mywin->params.mapX + (0 + useHeight) * mywin->params.mapY));

}

void	put_map(t_vars *mywin, t_img *img)
{
	int		x;
	int		y;
	int		col;
	int		squares_len;

	col = 0;
	squares_len = get_square_side(mywin);
	y = -1;
	while (++y < mywin->params.mapY)
	{
		x = -1;
		while (++x < mywin->params.mapX)
		{
			if (mywin->params.map[y][x] && mywin->params.map[y][x] <= '2' && mywin->params.map[y][x] >= '1')
			{
				if (mywin->params.map[y][x] == '1')
					col = 0x00020202;
				else if (mywin->params.map[y][x] == '2')
					col = 0x00505050;
				else
					col = 0x00FFFFFF;
				draw_square(img, x * squares_len, y * squares_len, squares_len, col);
			}
			if (mywin->params.map[y][x] && ft_strrchr("NSEW", mywin->params.map[y][x]))
			{
				mywin->player.x_pos = squares_len * x;
				mywin->player.y_pos = squares_len * y;
			}
		}
	}
}

void	build_image(t_vars *mywin, t_img *img)
{
	fill_window(mywin, img, 0x00808080);
	put_map(mywin, img);
	mlx_put_image_to_window(mywin->mlx, mywin->win, img->img, 0, 0);
}