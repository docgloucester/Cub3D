/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:41:59 by rgilles           #+#    #+#             */
/*   Updated: 2021/02/17 10:42:16 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	display_sprites(t_vars *mywin, t_sprite *sprites)
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
		center_stripe = mywin->params.res_x - 1 - ((sprites->angle + 0.167 * PI) * mywin->params.res_x) / (0.333 * PI);
		printf("Center stripe position is %d\n", center_stripe);
		while (x < width)
		{
			if ((x + center_stripe - width / 2 >= 0) && (x + center_stripe - width / 2 < mywin->params.res_x)
				&& sprites->norm < mywin->norms_array[x + center_stripe - width / 2])
			{
				draw_stripe(mywin, x + center_stripe - width / 2, height, &mywin->sprite, (float)x / (float)width * (float)get_square_side(mywin));
			}
			x++;
		}
		sprites = sprites->next;
	}
}