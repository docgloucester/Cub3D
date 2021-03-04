/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:35:39 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/04 13:35:51 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float			float_modulo(float a, float b)
{
	while (a >= b)
		a -= b;
	return (a);
}

void			chg_angle(t_player *player, float angle)
{
	while (angle < -PI)
		angle += 2 * PI;
	while (angle >= PI)
		angle -= 2 * PI;
	player->angle = angle;
	player->dx = cosf(angle);
	player->dy = -sinf(angle);
}

float			get_norm(t_point start, t_point end)
{
	return (sqrtf(powf(start.x - end.x, 2) + powf((start.y - end.y), 2)));
}

int				cmp_norm(t_point start, t_point end0, t_point end1)
{
	float	norm1;
	float	norm0;

	if (end0.x == -1)
		return (1);
	if (end1.x == -1)
		return (0);
	norm1 = get_norm(start, end1);
	norm0 = get_norm(start, end0);
	if (norm1 < norm0)
		return (1);
	return (0);
}
