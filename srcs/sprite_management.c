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
		return NULL;
	sprites->norm = norm;
	while (angle_diff < - PI)
		angle_diff += 2 * PI;
	while (angle_diff >= PI)
		angle_diff -= 2 * PI;
	sprites->angle = angle_diff;
	sprites->coord = coord;
	sprites->next = next;
	return (sprites);
}

void		addsprite(t_sprite **entry, t_point coord, float norm, float angle_diff)
{
	t_sprite *curr;

	if (!(*entry))
		*entry = newsprite(norm, angle_diff, coord, NULL);
	if ((*entry)->norm < norm)
		*entry = newsprite(norm, angle_diff, coord, *entry);
	curr = *entry;
	while (curr->next && curr->next->norm >= norm)
		curr = curr->next;
	if (curr->norm != norm)
		curr->next = newsprite(norm, angle_diff, coord, curr->next);
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
