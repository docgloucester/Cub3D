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

void		addsprite(t_sprite **entry, t_point coord, float norm, float diff)
{
	t_sprite *curr;

	if (!(*entry))
		*entry = newsprite(norm, diff, coord, NULL);
	if ((*entry)->norm < norm)
		*entry = newsprite(norm, diff, coord, *entry);
	curr = *entry;
	while (curr->next && curr->next->norm >= norm)
		curr = curr->next;
	if (curr->norm != norm)
		curr->next = newsprite(norm, diff, coord, curr->next);
}

void		display_sprites(t_vars *mywin, t_sprite *sprites)
{
	int height;
	int width;
	int	x;
	int	center_stripe;

	while (sprites)
	{
		x = 0;
		height = get_square_side(mywin) * mywin->params.res_y / sprites->norm;
		width = height * mywin->sprite.img.width / mywin->sprite.img.height;
		center_stripe = mywin->params.res_x - 1
		- ((sprites->angle + 0.167 * PI) * mywin->params.res_x) / (0.333 * PI);
		while (x < width)
		{
			if ((x + center_stripe - width / 2 >= 0)
				&& (x + center_stripe - width / 2 < mywin->params.res_x)
				&& sprites->norm < mywin->norms[x + center_stripe - width / 2])
			{
				draw_stripe(mywin, x + center_stripe - width / 2, sprites->norm,
					&mywin->sprite, 0.999 - (float)x / (float)width);
			}
			x++;
		}
		sprites = sprites->next;
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
