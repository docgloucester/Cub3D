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

void	place_player(t_vars *mywin, int col)
{
	t_point	start;

	start.x = mywin->player.x_pos - get_square_side(mywin) / 6;
	start.y = mywin->player.y_pos - get_square_side(mywin) / 6;
	draw_square(&mywin->player_img, start, get_square_side(mywin) / 3, col);
}

int		vertic_draw(t_point *start, t_coord coord1, int *err, t_point end)
{
	if (2 * *err <= coord1.x)
	{
		if ((int)start->y == (int)end.y)
			return (1);
		start->y += coord1.y;
		*err += coord1.x;
	}
	return (0);
}

int		isinrange(t_vars *mywin, t_point st)
{
	if (st.x >= 0 && st.y >= 0 && st.x < mywin->params.res_x
		&& st.y < mywin->params.res_y)
		return (1);
	return (0);
}

void	init_coord(t_coord *coord1, t_coord *coord2, t_point st, t_point end)
{
	coord1->x = (int)fabs(end.x - st.x);
	coord2->x = st.x < end.x ? 1 : -1;
	coord2->y = -(int)fabs(end.y - st.y);
	coord1->y = st.y < end.y ? 1 : -1;
}

void	draw_line(t_vars *mywin, t_point end)
{
	t_coord	coord1;
	t_coord	coord2;
	t_point	st;
	int		err;

	st.x = mywin->player.x_pos;
	st.y = mywin->player.y_pos;
	init_coord(&coord1, &coord2, st, end);
	err = coord1.x + coord2.y;
	while (1)
	{
		if (isinrange(mywin, st))
			my_pixelput(&mywin->player_img, (int)st.x, (int)st.y, 0x0000FF00);
		if (2 * err >= coord2.y)
		{
			if ((int)st.x == (int)end.x)
				break ;
			st.x += coord2.x;
			if (vertic_draw(&st, coord1, &err, end))
				break ;
			err += coord2.y;
		}
		else if (vertic_draw(&st, coord1, &err, end))
			break ;
	}
}
