/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 01:38:26 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/05 01:38:40 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_blocks(t_vars *mywin, int i, t_point v_end, t_point h_end, float diff)
{
	t_img	*text;
	t_point	end;
	int		comp_norm;
	float	norm;
	float	offset;
	t_point	normoffset;

	end = cmp_norm(mywin, h_end, v_end) ? v_end : h_end;
	comp_norm = cmp_norm(mywin, h_end, v_end);
	norm = cosf(diff) * get_norm(mywin, end);
	if (norm <= 0)
		norm = 1;
	if (comp_norm == 0)
	{
		offset = float_modulo(end.x, (float)get_square_side(mywin)) / get_square_side(mywin);
		if ((mywin->player.angle + diff >= -PI && mywin->player.angle + diff < 0)
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
			|| (mywin->player.angle + diff >= -1.5 * PI && mywin->player.angle + diff <= -0.5 * PI))
			text = &mywin->w_text;
		else
		{
			text = &mywin->e_text;
			offset = 0.999 - offset;
		}
	}
	normoffset.x = norm;
	normoffset.y = offset;
	draw_stripe(mywin, mywin->params.res_x - 1 - i, normoffset, text);
}

/*
** acos returns exclusively into the [0;pi] domain, since cos is only bijective
** on half of the circle so, in order to artificially "extend" its definition
** domains to cover our needs seamlessly we have to manually flip the result of
** acos for the "sprite angle" in the plane referential (thus, mathematically
** speaking, breaking the bijectivity of arcos but who cares...)
**
** when the player is "under" the sprite center, acos is unflipped
** when the player is "above, acos has to be flipped
*/

void	call_sprite(t_vars *mywin, t_point end, int squareside)
{
	t_point	sprite_center;

	sprite_center.x = (int)(end.x / squareside) * squareside + squareside / 2;
	sprite_center.y = (int)(end.y / squareside) * squareside + squareside / 2;
	if (mywin->player.y_pos >= sprite_center.y)
		addsprite(mywin, sprite_center, get_norm(mywin, sprite_center),
			acosf((sprite_center.x - mywin->player.x_pos)
			/ get_norm(mywin, sprite_center)) - mywin->player.angle);
	else
		addsprite(mywin, sprite_center, get_norm(mywin, sprite_center),
			-acosf((sprite_center.x - mywin->player.x_pos)
			/ get_norm(mywin, sprite_center)) - mywin->player.angle);
}

t_point	expand_ray(t_vars *mywin, t_point end, t_point delta_ray)
{
	int		reached_wall;
	int		squareside;

	reached_wall = 0;
	squareside = get_square_side(mywin);
	while (!reached_wall && end.x < mywin->params.res_x
		&& end.y < mywin->params.res_y && end.x >= 0 && end.y >= 0)
	{
		if ((int)(end.y / squareside) < 0 || (int)(end.x / squareside) < 0
			|| (int)((end.x) / squareside) >= mywin->params.map_x
			|| (int)((end.y) / squareside) >= mywin->params.map_y)
			break ;
		if (mywin->params.map[end.y / squareside][end.x / squareside] == '2')
		{
			call_sprite(mywin, end, squareside);
		}
		if (mywin->params.map[end.y / squareside][end.x / squareside] == '1')
			reached_wall = 1;
		else
		{
			end.x += delta_ray.x;
			end.y += delta_ray.y;
		}
	}
	return (end);
}
