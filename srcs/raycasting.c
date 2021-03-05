/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:16:41 by rgilles           #+#    #+#             */
/*   Updated: 2020/09/14 15:16:43 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_point	gethorray(t_vars *mw, float angle, t_point *delta_ray)
{
	t_point end;
	int		squareside;

	squareside = get_square_side(mw);
	if (angle == 0 || angle == PI)
	{
		end.y = mw->player.y_pos;
		end.x = mw->player.x_pos;
	}
	else if (angle < PI)
	{
		end.y = ((int)mw->player.y_pos / squareside) * squareside - 0.0001;
		end.x = mw->player.x_pos - (end.y - mw->player.y_pos) / tan(angle);
		delta_ray->y = -squareside;
		delta_ray->x = -delta_ray->y / tan(angle);
	}
	else
	{
		end.y = ((int)mw->player.y_pos / squareside) * squareside + squareside;
		end.x = mw->player.x_pos - (end.y - mw->player.y_pos) / tan(angle);
		delta_ray->y = squareside;
		delta_ray->x = -delta_ray->y / tan(angle);
	}
	return (end);
}

t_point	getverray(t_vars *mw, float angle, t_point *delta_ray)
{
	t_point end;
	int		squareside;

	squareside = get_square_side(mw);
	if (angle == 0.5 * PI || angle == 1.5 * PI)
	{
		end.y = mw->player.y_pos;
		end.x = mw->player.x_pos;
	}
	else if (angle > 0.5 * PI && angle < 1.5 * PI)
	{
		end.x = ((int)mw->player.x_pos / squareside) * squareside - 0.0001;
		end.y = mw->player.y_pos - (end.x - mw->player.x_pos) * tan(angle);
		delta_ray->x = -squareside;
		delta_ray->y = -delta_ray->x * tan(angle);
	}
	else
	{
		end.x = ((int)mw->player.x_pos / squareside) * squareside + squareside;
		end.y = mw->player.y_pos - (end.x - mw->player.x_pos) * tan(angle);
		delta_ray->x = squareside;
		delta_ray->y = -delta_ray->x * tan(angle);
	}
	return (end);
}

float	range_angle(float angle)
{
	while (angle <= 0)
		angle += 2 * PI;
	while (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	draw_rays(t_vars *mywin, int i)
{
	float		angle;
	t_point		h_end;
	t_point		v_end;
	t_point		half;
	float		diff;

	fill_window(mywin, &mywin->fps_img, mywin->params.ceilg_col);
	half.x = 0;
	half.y = (int)(mywin->params.res_y / 2.0);
	draw_rect(mywin, half, mywin->params.res_x, mywin->params.res_y / 2);
	diff = -0.167 * PI;
	mywin->sprites = NULL;
	while (++i < mywin->params.res_x)
	{
		angle = range_angle(mywin->player.angle + diff);
		h_end = expand_ray(mywin, gethorray(mywin, angle, &half), half);
		v_end = expand_ray(mywin, getverray(mywin, angle, &half), half);
		draw_line(mywin, cmp_norm(mywin, h_end, v_end) ? v_end : h_end);
		mywin->norms[mywin->params.res_x - 1 - i] = get_norm(mywin,
			cmp_norm(mywin, h_end, v_end) ? v_end : h_end);
		put_blocks(mywin, i, v_end, h_end, diff);
		diff += 0.333 * PI / (float)mywin->params.res_x;
	}
	display_sprites(mywin);
	freesprite(mywin->sprites);
}
