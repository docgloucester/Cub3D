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

void	addsprite(t_sprite *sprites, float norm, float angle_diff)
{
	while (sprites != NULL)
		sprites = sprites->next;
	sprites = (t_sprite*)(malloc(sizeof(t_sprite)));
	sprites->norm = norm;
	sprites->angle = angle_diff;
	sprites->next = NULL;
}

void	freesprite(t_sprite *sprites)
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
