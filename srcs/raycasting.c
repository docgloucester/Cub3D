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

void	put_blocks(t_vars *mywin, int i, float norm, int cmpNorm, float angle)
{
	int		col;
	t_point	block_dims;

	if (norm <= 0)
		norm = 1;
	block_dims.y = (int)((float)get_square_side(mywin) * mywin->params.res_y / norm);
	block_dims.x = (int)(mywin->params.res_x / 840.0 + 1.0);
	if (block_dims.y > mywin->params.res_y)
		block_dims.y = mywin->params.res_y;
	if (!cmpNorm)
	{
		if (angle <= PI)
			col = 0x000000FF;
		else
			col = 0x0000D050;
	}
	else
		if (angle >= 0.5 * PI && angle <= 1.5 * PI)
			col = 0x000050D0;
		else
			col = 0x0000FF00;
	draw_block(mywin, (int)((839.0 - (float)i) * mywin->params.res_x / 840.0), block_dims, col);
}

t_point	getHorRay(t_vars *mywin, t_point start, float angle)
{
	t_point end;
	t_point	delta_ray;
	int		reached_wall;
	int		squareside = get_square_side(mywin);

	reached_wall = 0;
	if (angle == 0 || angle == PI)
	{
		end.y = start.y;
		end.x = start.x;
		reached_wall = 1;
	}
	else if (angle < PI)
	{
		end.y = ((int)start.y / squareside) * squareside - 0.0001;
		end.x = start.x - (end.y - start.y) / tan(angle);
		delta_ray.y = - squareside;
		delta_ray.x = - delta_ray.y / tan(angle);
	}
	else if (angle > PI)
	{
		end.y = ((int)start.y / squareside) * squareside + squareside;
		end.x = start.x - (end.y - start.y) / tan(angle);
		delta_ray.y = squareside;
		delta_ray.x = - delta_ray.y / tan(angle);
	}
	while (!reached_wall)
	{
		if ((int)((end.y) / squareside) < 0 || (int)((end.x) / squareside) < 0
			|| (int)((end.x) / squareside) >= mywin->params.mapX
			|| (int)((end.y) / squareside) >= mywin->params.mapY)
			break;
		if (ft_strchr("12", mywin->params.map[(int)(end.y / squareside)][(int)(end.x / squareside)]))
			reached_wall = 1;
		else
		{
			end.x += delta_ray.x;
			end.y += delta_ray.y;
		}
	}
	return (end);
}

t_point	getVerRay(t_vars *mywin, t_point start, float angle)
{
	t_point end;
	t_point	delta_ray;
	int		reached_wall;
	int		squareside = get_square_side(mywin);

	reached_wall = 0;
	if (angle == 0.5 * PI || angle == 1.5 * PI)
	{
		end.y = start.y;
		end.x = start.x;
		reached_wall = 1;
	}
	else if (angle > 0.5 * PI && angle < 1.5 * PI)
	{
		end.x = ((int)start.x / squareside) * squareside - 0.0001;
		end.y = start.y - (end.x - start.x) * tan(angle);
		delta_ray.x = - squareside;
		delta_ray.y = - delta_ray.x * tan(angle);
	}
	else
	{
		end.x = ((int)start.x / squareside) * squareside + squareside;
		end.y = start.y - (end.x - start.x) * tan(angle);
		delta_ray.x = squareside;
		delta_ray.y = - delta_ray.x * tan(angle);
	}
	while (!reached_wall)
	{
		if ((int)((end.y) / squareside) < 0 || (int)((end.x) / squareside) < 0
			|| (int)((end.x) / squareside) >= mywin->params.mapX
			|| (int)((end.y) / squareside) >= mywin->params.mapY)
			break;
		if (ft_strchr("12", mywin->params.map[(int)((end.y) / squareside)][(int)((end.x) / squareside)]))
			reached_wall = 1;
		else
		{
			end.x += delta_ray.x;
			end.y += delta_ray.y;
		}
	}
	return (end);
}

void	drawRays(t_vars *mywin)
{
	float	angle;
	t_point start;
	t_point h_end;
	t_point v_end;
	float	diff;
	int		i;

	fill_window(mywin, &mywin->fps_img, mywin->params.ceilg_col);
	diff = -0.167 * PI;
	i = -1;
	while (diff <= 0.166 * PI)
	{
		angle = mywin->player.angle + diff;
		while (angle <= 0)
			angle += 2 * PI;
		while (angle > 2 * PI)
			angle -= 2 * PI;
		start.x = mywin->player.x_pos;
		start.y = mywin->player.y_pos;
		h_end = getHorRay(mywin, start, angle);
		v_end = getVerRay(mywin, start, angle);
		draw_line(mywin, start, cmpNorm(start, h_end, v_end) ? v_end: h_end, 0x0000FF00);
		put_blocks(mywin, ++i, cosf(diff) * getNorm(start, cmpNorm(start, h_end, v_end) ? v_end: h_end), cmpNorm(start, h_end, v_end), angle);
		diff += 0.00125;
	}
}
