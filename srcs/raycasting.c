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

void	put_blocks(t_vars *mywin, int i, t_point start, t_point v_end, t_point h_end, float diff)
{
	t_texture	*text;
	int			stripe_height;
	t_point		end;
	int			comp_norm;
	float		norm;
	float		offset;

	end = cmp_norm(start, h_end, v_end)? v_end: h_end;
	comp_norm = cmp_norm(start, h_end, v_end);
	norm = cosf(diff) * get_norm(start, end);
	if (norm <= 0)
		norm = 1;
	stripe_height = get_square_side(mywin) * mywin->params.res_y / norm;
	if (comp_norm == 0)
	{
		if ((mywin->player.angle + diff >= - PI && mywin->player.angle + diff < 0)
			|| (mywin->player.angle + diff >= PI && mywin->player.angle + diff < 2 * PI))
			text = &mywin->s_text;
		else
			(text = &mywin->n_text);
		offset = float_modulo(end.x, (float)get_square_side(mywin));
	}
	else
	{
		if (mywin->player.angle + diff >= 0.5 * PI && mywin->player.angle + diff <= 1.5 * PI)
			text = &mywin->w_text;
		else
			text = &mywin->e_text;
		offset = float_modulo(end.y, (float)get_square_side(mywin));
	}
	draw_block(mywin, mywin->params.res_x - 1 - i, stripe_height, text, offset);
}

void	set_sprite(t_vars *mywin, int i, t_point start, t_point end, float diff)
{

	static int		prev_i;
	float			norm;
	float			offset;

	if (prev_i != i - 1)
	{
		norm = cosf(diff) * get_norm(start, end);
		offset = sqrtf(powf(float_modulo(end.y, (float)get_square_side(mywin)), 2) + powf(float_modulo(end.x, (float)get_square_side(mywin)), 2));
		mywin->sprites_array[2 * i] = norm;
		mywin->sprites_array[2 * i + 1] = offset;
	}
	prev_i = i;
}

void	draw_sprites(t_vars *mywin)
{
	int	i;
	int y;
	int	y_start;
	int	sprite_offset;
	int	height;
	int	width;
	int col;

	i = 0;
	while (i < mywin->params.res_x)
	{
		if (mywin->sprites_array[2 * i] != 0)
		{
			height = get_square_side(mywin) * mywin->params.res_y / mywin->sprites_array[2 * i];
			y_start = (mywin->params.res_y - height) / 2;
			width = mywin->sprite.img.width * height / mywin->sprite.img.height;
			sprite_offset = mywin->sprites_array[2 * i + 1] / sqrtf(2 * powf(get_square_side(mywin), 2)) * mywin->sprite.img.width;
			while (sprite_offset < mywin->sprite.img.width)
			{
				y = -1;
				while (++y < height)
				{
					if (y + y_start>= 0 && y + y_start < mywin->params.res_y)
					{
						col = get_pixel(&mywin->sprite.img, mywin->sprite.img.width - 1 - sprite_offset, (int)((float)y / (float)height * (float)mywin->sprite.img.height));
						if (col << 8 != 0)
							my_pixelput(&mywin->fps_img, i, y + y_start, col);
					}
				}
				sprite_offset += mywin->sprites_array[2 * i] * sinf(0.333 * PI / (float)mywin->params.res_x);
				i++;
			}
		}
		i++;
	}
}

t_point	expand_ray(t_vars *mywin, t_point end, t_point delta_ray, t_point *sprite)
{
	int reached_wall;
	int	squareside;

	reached_wall = 0;
	squareside = get_square_side(mywin);
	while (!reached_wall)
	{
		if ((int)((end.y) / squareside) < 0 || (int)((end.x) / squareside) < 0
			|| (int)((end.x) / squareside) >= mywin->params.map_x
			|| (int)((end.y) / squareside) >= mywin->params.map_y)
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

t_point	gethorray(t_vars *mywin, t_point start, float angle, t_point *delta_ray)
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

t_point	getverray(t_vars *mywin, t_point start, float angle, t_point *delta_ray)
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

void	draw_rays(t_vars *mywin)
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
		sprite_h.x = -1;
		sprite_h.y = -1;
		sprite_v.x = -1;
		sprite_v.y = -1;
		h_end = expand_ray(mywin, gethorray(mywin, start, angle, &half), half, &sprite_h);
		v_end = expand_ray(mywin, getverray(mywin, start, angle, &half), half, &sprite_v);
		draw_line(mywin, start, cmp_norm(start, h_end, v_end) ? v_end: h_end, 0x0000FF00);
		mywin->norms_array[++i] = get_norm(start, cmp_norm(start, h_end, v_end) ? v_end: h_end);
		put_blocks(mywin, i, start, v_end, h_end, diff);
		if ((sprite_v.x != -1 && cmp_norm(start,cmp_norm(start, h_end, v_end) ? v_end: h_end, sprite_v))
			|| (sprite_h.x != -1 && cmp_norm(start,cmp_norm(start, h_end, v_end) ? v_end: h_end, sprite_h)))
		{
			set_sprite(mywin, i, start, cmp_norm(start, sprite_h, sprite_v)? sprite_v: sprite_h, diff);
		}
		diff += 0.333 * PI / (float)mywin->params.res_x;
	}
	draw_sprites(mywin);
}
