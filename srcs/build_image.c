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
	int	hor;
	int	ver;

	hor = mywin->params.res_x / mywin->params.map_x;
	ver = mywin->params.res_y / mywin->params.map_y;
	// ft_printf("resy is %d and mapy is %d\n\n", mywin->params.res_y, mywin->params.map_y);
	// ft_printf("resx is %d and mapx is %d\n\n", mywin->params.res_x, mywin->params.map_x);
	// ft_printf("ver gss is %d\nhor gss is %d\n\n", ver, hor);
	if (ver < hor)
		return (ver);
	return (hor);
}

void	put_map(t_vars *mywin, t_img *img)
{
	int		x;
	int		y;
	int		squares_len;
	char	*uwu;
	char	*owo;

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
					draw_square(img, x * squares_len, y * squares_len, squares_len,
					0x00020202);
				else if (mywin->params.map[y][x] == '2')
					draw_square(img, x * squares_len + squares_len / 2, y * squares_len + squares_len / 2, squares_len / 4,
					0x00505050);
			}
			owo = "ENWS";
			if (mywin->params.map[y][x]
				&& (uwu = ft_strchr(owo, mywin->params.map[y][x])))
			{
				change_angle(&mywin->player, PI / 2 * (int)(uwu - owo));
				mywin->player.x_pos = squares_len * x + squares_len / 2;
				mywin->player.y_pos = squares_len * y + squares_len / 2;
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
	fill_window(mywin, &(mywin->player_img), 0xFFFFFFFF);
	fill_window(mywin, img, 0x00808080);
	put_map(mywin, img);
	place_player(mywin, 0x00FF0000);
	draw_rays(mywin);
}
