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

t_sprite	*newsprite(float norm, float angle_diff)
{
	t_sprite	*sprites;

	if (!(sprites = (t_sprite*)(malloc(sizeof(t_sprite)))))
		return NULL;
	sprites->norm = norm;
	sprites->angle = angle_diff;
	sprites->next = NULL;
	return (sprites);
}

void		addsprite(t_sprite **entry, float norm, float angle_diff)
{
	int i = 0;
	t_sprite *curr;

	if (!(*entry))
		*entry = newsprite(norm, angle_diff);
	curr = *entry;
	while (curr->next)
	{
		i++;
		curr = curr->next;
	}
	printf("Jumped %d times to insert sprite\n", i);
	curr->next = newsprite(norm, angle_diff);
}

void		freesprite(t_sprite *sprites)
{
	t_sprite *next;

	while (sprites && sprites->next != NULL)
	{
		next = sprites->next;
		free(sprites);
		sprites = next;
	}
	free(sprites);
}
