/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:35:39 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/04 13:35:51 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	float_modulo(float a, float b)
{
	while (a >= b)
		a -= b;
	return (a);
}

void	chg_angle(t_player *player, float angle)
{
	while (angle < -PI)
		angle += 2 * PI;
	while (angle >= PI)
		angle -= 2 * PI;
	player->angle = angle;
	player->dx = cosf(angle);
	player->dy = -sinf(angle);
}

float	get_norm(t_vars *mywin, t_point end)
{
	t_point	start;

	start.x = mywin->player.x_pos;
	start.y = mywin->player.y_pos;
	return (sqrtf(powf(start.x - end.x, 2) + powf((start.y - end.y), 2)));
}

int		cmp_norm(t_vars *mywin, t_point end0, t_point end1)
{
	float	norm1;
	float	norm0;

	if (end0.x == -1)
		return (1);
	if (end1.x == -1)
		return (0);
	norm1 = get_norm(mywin, end1);
	norm0 = get_norm(mywin, end0);
	if (norm1 < norm0)
		return (1);
	return (0);
}

void	draw_stripe(t_vars *mywin, int x_start, t_point normoffset, t_img *text)
{
	int		y;
	int		y_start;
	int		col;
	int		height;

	height = get_square_side(mywin) * mywin->params.res_y / normoffset.x;
	y_start = (mywin->params.res_y - height) / 2;
	y = -1;
	while (++y < height)
	{
		if (y_start + y >= 0 && y_start + y < mywin->params.res_y)
		{
			col = get_pixel(text, text->width - 1 -
				(int)(normoffset.y * (float)text->width),
				(int)((float)y / (float)height * (float)text->height));
			if (col << 8 != 0)
				my_pixelput(&mywin->fps_img, x_start, y_start + y, col);
		}
	}
}
