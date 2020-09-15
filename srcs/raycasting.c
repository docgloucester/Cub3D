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

t_point	getHorRay(t_vars *mywin, float angle)
{
	t_point end;
	t_ray	ray;
	int		reached_wall;
	int		squareside = get_square_side(mywin);

	reached_wall = 0;

	
	
	return (end);
}

void	drawRays(t_vars *mywin)
{
	float angle;
	t_point start;
	t_point end;

	angle = mywin->player.angle;
	start.x = mywin->player.x_pos;
	start.y = mywin->player.y_pos;
	end = getHorRay(mywin, angle);
	draw_line(&mywin->player_img, start, end, 0x0000FF00);
}
