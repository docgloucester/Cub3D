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
	t_point		end;
	int			comp_norm;
	float		norm;
	float		offset;

	end = cmp_norm(start, h_end, v_end)? v_end: h_end;
	comp_norm = cmp_norm(start, h_end, v_end);
	norm = cosf(diff) * get_norm(start, end);
	if (norm <= 0)
		norm = 1;
	if (comp_norm == 0)
	{
		offset = float_modulo(end.x, (float)get_square_side(mywin)) / get_square_side(mywin);
		if ((mywin->player.angle + diff >= - PI && mywin->player.angle + diff < 0)
			|| (mywin->player.angle + diff >= PI && mywin->player.angle + diff < 2 * PI))
			text = &mywin->s_text;
		else
		{
			(text = &mywin->n_text);
			offset = 0.999 - offset;
		}
	}
	else
	{
		offset = float_modulo(end.y, (float)get_square_side(mywin)) / get_square_side(mywin);
		if ((mywin->player.angle + diff >= 0.5 * PI && mywin->player.angle + diff <= 1.5 * PI)
			||(mywin->player.angle + diff >= -1.5 * PI && mywin->player.angle + diff <= -0.5 * PI))
			text = &mywin->w_text;
		else
		{
			text = &mywin->e_text;
			offset = 0.999 - offset;
		}
	}
	draw_stripe(mywin, mywin->params.res_x - 1 - i, norm, text, offset);
}

/* acos returns exclusively into the [0;pi] domain, since cos is only bijective on half of the circle
** so, in order to artificially "extend" its definition domains to cover our needs seamlessly
** we have to manually flip the result of acos for the "sprite angle" in the plane referential
** (thus, mathematically speaking, breaking the bijectivity of arcos but who cares...)
**
** when the player is "under" the sprite center, acos is unflipped
** when the player is "above, acos has to be flipped
*/

t_point	expand_ray(t_vars *mywin, t_point end, t_point delta_ray, float diff, t_sprite **sprites)
{
	int 	reached_wall;
	int		squareside;
	t_point	player_pos;
	t_point sprite_center;

	reached_wall = 0;
	(void)diff;
	squareside = get_square_side(mywin);
	player_pos.x = mywin->player.x_pos;
	player_pos.y = mywin->player.y_pos;
	while (!reached_wall && end.x < mywin->params.res_x && end.y < mywin->params.res_y && end.x >=0 && end.y >= 0)
	{
		if ((int)(end.y / squareside) < 0 || (int)(end.x / squareside) < 0
			|| (int)((end.x) / squareside) >= mywin->params.map_x
			|| (int)((end.y) / squareside) >= mywin->params.map_y)
			break;
		if (mywin->params.map[(int)(end.y / squareside)][(int)(end.x / squareside)] == '2')
		{
			sprite_center.x = (int)(end.x / squareside) * squareside + squareside / 2;
			sprite_center.y = (int)(end.y / squareside) * squareside + squareside / 2;
			if (player_pos.y >= sprite_center.y)
				addsprite(sprites, sprite_center, get_norm(player_pos, sprite_center), acosf((sprite_center.x - player_pos.x) / get_norm(player_pos, sprite_center)) - mywin->player.angle);
			else
				addsprite(sprites, sprite_center, get_norm(player_pos, sprite_center), - acosf((sprite_center.x - player_pos.x) / get_norm(player_pos, sprite_center)) - mywin->player.angle);
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
	float		angle;
	t_point		start;
	t_point		h_end;
	t_point		v_end;
	t_point		half;
	float		diff;
	int			i;
	t_sprite	*sprites;

	fill_window(mywin, &mywin->fps_img, mywin->params.ceilg_col);
	half.x = 0;
	half.y = (int)(mywin->params.res_y / 2.0);
	draw_rect(&mywin->fps_img, half, mywin->params.res_x, mywin->params.res_y / 2, mywin->params.floor_col);
	diff = -0.167 * PI;
	i = -1;
	sprites = NULL;
	while (++i < mywin->params.res_x)
	{
		angle = mywin->player.angle + diff;
		while (angle <= 0)
			angle += 2 * PI;
		while (angle > 2 * PI)
			angle -= 2 * PI;
		start.x = mywin->player.x_pos;
		start.y = mywin->player.y_pos;
		h_end = expand_ray(mywin, gethorray(mywin, start, angle, &half), half, diff, &sprites);
		v_end = expand_ray(mywin, getverray(mywin, start, angle, &half), half, diff, &sprites);
		draw_line(mywin, start, cmp_norm(start, h_end, v_end) ? v_end: h_end, 0x0000FF00);
		mywin->norms[mywin->params.res_x - 1 - i] = get_norm(start, cmp_norm(start, h_end, v_end) ? v_end: h_end);
		put_blocks(mywin, i, start, v_end, h_end, diff);
		diff += 0.333 * PI / (float)mywin->params.res_x;
	}
	display_sprites(mywin, sprites);
	freesprite(sprites);
}
