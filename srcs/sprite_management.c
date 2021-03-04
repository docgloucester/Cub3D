/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:19:11 by rgilles           #+#    #+#             */
/*   Updated: 2021/02/09 16:19:14 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_sprite	*newsprite(float norm, float angle_diff, t_point coord, void *next)
{
	t_sprite	*sprites;

	if (!(sprites = (t_sprite*)(malloc(sizeof(t_sprite)))))
		return (NULL);
	sprites->norm = norm;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	while (angle_diff >= PI)
		angle_diff -= 2 * PI;
	sprites->angle = angle_diff;
	sprites->coord = coord;
	sprites->next = next;
	return (sprites);
}

void		addsprite(t_vars *mywin, t_point coord, float norm, float diff)
{
	t_sprite *curr;

	while (diff < -PI)
		diff += 2 * PI;
	while (diff > PI)
		diff -= 2 * PI;
	if (!(mywin->sprites))
		mywin->sprites = newsprite(norm, diff, coord, NULL);
	if (mywin->sprites->norm < norm)
		mywin->sprites = newsprite(norm, diff, coord, mywin->sprites);
	curr = mywin->sprites;
	while (curr->next && curr->next->norm >= norm)
		curr = curr->next;
	if (!(curr->norm == norm && curr->angle == diff))
		curr->next = newsprite(norm, diff, coord, curr->next);
}

void		display_sprites(t_vars *mywin)
{
	int			width;
	int			x;
	int			center_stripe;
	t_sprite	*curr;
	t_point		normoffset;

	curr = mywin->sprites;
	while (curr && (x = -1))
	{
		width = get_square_side(mywin) * mywin->params.res_y / curr->norm
			* mywin->sprite.width / mywin->sprite.height;
		center_stripe = mywin->params.res_x - 1
			- ((curr->angle + 0.167 * PI) * mywin->params.res_x) / (0.333 * PI);
		while (++x < width)
			if ((x + center_stripe - width / 2 >= 0)
				&& (x + center_stripe - width / 2 < mywin->params.res_x)
				&& curr->norm < mywin->norms[x + center_stripe - width / 2])
			{
				normoffset.x = curr->norm;
				normoffset.y = 0.999 - (float)x / (float)width;
				draw_stripe(mywin, x + center_stripe - width / 2, normoffset,
					&mywin->sprite);
			}
		curr = curr->next;
	}
}

void		freesprite(t_sprite *sprites)
{
	t_sprite *next;

	while (sprites)
	{
		next = sprites->next;
		free(sprites);
		sprites = next;
	}
}
