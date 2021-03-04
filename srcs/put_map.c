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
	if (ver < hor)
		return (ver);
	return (hor);
}

void	place_player(t_vars *mywin, int col)
{
	draw_square(&mywin->player_img,
		mywin->player.x_pos - get_square_side(mywin) / 6,
		mywin->player.y_pos - get_square_side(mywin) / 6,
		get_square_side(mywin) / 3, col);
}

void	start_pos(t_vars *mywin, int x, int y, int sq)
{
	char	*uwu;
	char	*owo;

	owo = "ENWS";
	if (mywin->params.map[y][x]
		&& (uwu = ft_strchr(owo, mywin->params.map[y][x])))
	{
		chg_angle(&mywin->player, PI / 2 * (int)(uwu - owo));
		mywin->player.x_pos = sq * x + sq / 2;
		mywin->player.y_pos = sq * y + sq / 2;
	}
}

void	put_map(t_vars *mywin, t_img *img)
{
	int		x;
	int		y;
	int		sq;

	sq = get_square_side(mywin);
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
					draw_square(img, x * sq, y * sq, sq, 0x00020202);
				else
					draw_square(img, x * sq + sq / 2, y * sq + sq / 2, sq / 4,
					0x00505050);
			}
			start_pos(mywin, x, y, sq);
		}
	}
}
