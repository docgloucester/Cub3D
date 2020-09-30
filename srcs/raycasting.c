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
	t_texture	*text;
	t_point	block_dims;

	if (norm <= 0)
		norm = 1;
	block_dims.y = (int)((float)get_square_side(mywin) * mywin->params.res_y / norm);
	block_dims.x = (int)(mywin->params.res_x / 837.0 + 1.0);
	if (cmpNorm == 0)
		if (angle <= PI)
			text = &mywin->n_text;
		else
			text = &mywin->s_text;
	else
		if (angle >= 0.5 * PI && angle <= 1.5 * PI)
			text = &mywin->w_text;
		else
			text = &mywin->e_text;
	draw_block(mywin, (int)((836.0 - (float)i) * mywin->params.res_x / 837.0), block_dims, text);
}

void	put_sprite(t_vars *mywin, int i, float norm)
{
	t_point	sprite_chunk_dims;

	if (norm <= 0)
		norm = 1;
	sprite_chunk_dims.y = (int)((float)get_square_side(mywin) * mywin->params.res_y / norm);
	sprite_chunk_dims.x = (int)(mywin->params.res_x / 837.0 + 1.0);
	draw_block(mywin, (int)((836.0 - (float)i) * mywin->params.res_x / 837.0), sprite_chunk_dims, &mywin->sprite);
}

t_point	expand_dong(t_vars *mywin, t_point end, t_point delta_ray, t_point *sprite)
{
	int reached_wall;
	int	squareside;

	reached_wall = 0;
	squareside = get_square_side(mywin);
	while (!reached_wall)
	{
		if ((int)((end.y) / squareside) < 0 || (int)((end.x) / squareside) < 0
			|| (int)((end.x) / squareside) >= mywin->params.mapX
			|| (int)((end.y) / squareside) >= mywin->params.mapY)
			break;
		if (mywin->params.map[(int)((end.y) / squareside)][(int)((end.x) / squareside)] == '2')
		{
			sprite->x = end.x;
			sprite->y = end.y;
		}
		if (mywin->params.map[(int)((end.y) / squareside)][(int)((end.x) / squareside)] == '1')
			reached_wall = 1;
		else
		{
			end.x += delta_ray.x;
			end.y += delta_ray.y;
		}
	}
	return (end);
}

t_point	getHorRay(t_vars *mywin, t_point start, float angle, t_point *delta_ray)
{
	t_point end;
	int		squareside = get_square_side(mywin);

	if (angle == 0 || angle == PI)
	{
		end.y = start.y;
		end.x = start.x;
	}
	else if (angle < PI)
	{
		end.y = ((int)start.y / squareside) * squareside - 0.0001;
		end.x = start.x - (end.y - start.y) / tan(angle);
		delta_ray->y = - squareside;
		delta_ray->x = - delta_ray->y / tan(angle);
	}
	else
	{
		end.y = ((int)start.y / squareside) * squareside + squareside;
		end.x = start.x - (end.y - start.y) / tan(angle);
		delta_ray->y = squareside;
		delta_ray->x = - delta_ray->y / tan(angle);
	}
	return (end);
}

t_point	getVerRay(t_vars *mywin, t_point start, float angle, t_point *delta_ray)
{
	t_point end;
	int		squareside = get_square_side(mywin);

	if (angle == 0.5 * PI || angle == 1.5 * PI)
	{
		end.y = start.y;
		end.x = start.x;
	}
	else if (angle > 0.5 * PI && angle < 1.5 * PI)
	{
		end.x = ((int)start.x / squareside) * squareside - 0.0001;
		end.y = start.y - (end.x - start.x) * tan(angle);
		delta_ray->x = - squareside;
		delta_ray->y = - delta_ray->x * tan(angle);
	}
	else
	{
		end.x = ((int)start.x / squareside) * squareside + squareside;
		end.y = start.y - (end.x - start.x) * tan(angle);
		delta_ray->x = squareside;
		delta_ray->y = - delta_ray->x * tan(angle);
	}
	return (end);
}

void	drawRays(t_vars *mywin)
{
	float	angle;
	t_point start;
	t_point h_end;
	t_point v_end;
	t_point half;
	float	diff;
	int		i;
	t_point sprite_h;
	t_point sprite_v;

	fill_window(mywin, &mywin->fps_img, mywin->params.ceilg_col);
	half.x = 0;
	half.y = (int)(mywin->params.res_y / 2.0);
	draw_rect(&mywin->fps_img, half, mywin->params.res_x, mywin->params.res_y / 2, mywin->params.floor_col);
	mywin->n_text.i = 0;
	mywin->s_text.i = 0;
	mywin->w_text.i = 0;
	mywin->e_text.i = 0;
	mywin->sprite.i = 0;
	sprite_h.x = -1;
	sprite_h.y = -1;
	sprite_v.x = -1;
	sprite_v.y = -1;
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
		h_end = expand_dong(mywin, getHorRay(mywin, start, angle, &half), half, &sprite_h);
		v_end = expand_dong(mywin, getVerRay(mywin, start, angle, &half), half, &sprite_v);
		draw_line(mywin, start, cmpNorm(start, h_end, v_end)? v_end: h_end, 0x0000FF00);
		put_blocks(mywin, ++i, cosf(diff) * getNorm(start, cmpNorm(start, h_end, v_end)? v_end: h_end), cmpNorm(start, h_end, v_end), angle);
		// if ((sprite_v.x != -1 && cmpNorm(start,cmpNorm(start, h_end, v_end)? v_end: h_end, sprite_v))
		// 	|| (sprite_h.x != -1 && cmpNorm(start,cmpNorm(start, h_end, v_end)? v_end: h_end, sprite_h)))
		// {
		// 	put_sprite(mywin, i - 1, cosf(diff) * getNorm(start, cmpNorm(start, sprite_h, sprite_v)? sprite_v: sprite_h));
		// }
		diff += 0.00125;
	}
}
