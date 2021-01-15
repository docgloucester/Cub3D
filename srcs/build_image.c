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
	int	use_height;

	use_height = 1;
	if (mywin->params.map_y < mywin->params.map_x)
		use_height = 0;
	return (((1 - use_height) * mywin->params.res_x
		+ (0 + use_height) * mywin->params.res_y)
		/ ((1 - use_height) * mywin->params.map_x
		+ (0 + use_height) * mywin->params.map_y));
}

void	put_map(t_vars *mywin, t_img *img)
{
	int		x;
	int		y;
	int		col;
	int		squares_len;
	char	*uwu;
	char	*owo;

	col = 0;
	squares_len = get_square_side(mywin);
	y = -1;
	while (++y < mywin->params.map_y)
	{
		x = -1;
		while (++x < mywin->params.map_x)
		{
			if (mywin->params.map[y][x]
				&& ft_strchr("12", mywin->params.map[y][x]))
			{
				if (mywin->params.map[y][x] == '1')
					col = 0x00020202;
				else if (mywin->params.map[y][x] == '2')
					col = 0x00505050;
				draw_square(img, x * squares_len, y * squares_len, squares_len,
					col);
			}
			owo = "ENWS";
			if (mywin->params.map[y][x]
				&& (uwu = ft_strchr(owo, mywin->params.map[y][x])))
			{
				change_angle(&mywin->player, PI / 2 * (int)(uwu - owo));
				mywin->player.x_pos = squares_len * x + 1;
				mywin->player.y_pos = squares_len * y + 1;
			}
		}
	}
}

void	place_player(t_vars *mywin, int col)
{
	draw_square(&mywin->player_img,
		mywin->player.x_pos - get_square_side(mywin) / 6,
		mywin->player.y_pos - get_square_side(mywin) / 6,
		get_square_side(mywin) / 3, col);
}

void	build_image(t_vars *mywin, t_img *img)
{
	fill_window(mywin, img, 0x00808080);
	put_map(mywin, img);
	place_player(mywin, 0x00FF0000);
	draw_rays(mywin);
	draw_player_dir(mywin, 0x00FF0000);
}
