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

t_point	getHorRay(t_vars *mywin, t_point start, float angle)
{
	t_point end;
	t_point	delta_ray;
	int		reached_wall;
	int		squareside = get_square_side(mywin);

	reached_wall = 0;
	if (angle == 0 || angle == PI)
	{
		end.y = start.y;
		end.x = start.x;
		reached_wall = 3;
	}
	else if (angle < PI)
	{
		end.y = ((int)start.y / squareside) * squareside - 0.0001;
		end.x = start.x - (end.y - start.y) / tan(angle);
		delta_ray.y = - squareside;
		delta_ray.x = - delta_ray.y / tan(angle);
	}
	else
	{
		end.y = ((int)start.y / squareside) * squareside + squareside;
		end.x = start.x - (end.y - start.y) / tan(angle);
		delta_ray.y = squareside;
		delta_ray.x = - delta_ray.y / tan(angle);
	}
	while (!reached_wall)
	{

		if (ft_strchr("12", mywin->params.map[(int)((end.y) / squareside)][(int)((end.x) / squareside)]))
			reached_wall = 1;
		else
		{
			end.x += delta_ray.x;
			end.y += delta_ray.y;
		}
	}
	return (end);
}

// t_point	getVerRay(t_vars *mywin, t_point start, float angle)
// {
// 	t_point end;
// 	t_point	delta_ray;
// 	int		reached_wall;
// 	int		squareside = get_square_side(mywin);

// 	reached_wall = 0;
// 	if (angle == 0 || angle == PI)
// 	{
// 		end.y = start.y;
// 		end.x = start.x;
// 		reached_wall = 3;
// 	}
// 	else if (angle < PI)
// 	{
// 		end.y = ((int)start.y / squareside) * squareside - 0.0001;
// 		end.x = start.x - (end.y - start.y) / tan(angle);
// 		delta_ray.y = - squareside;
// 		delta_ray.x = - delta_ray.y / tan(angle);
// 	}
// 	else
// 	{
// 		end.y = ((int)start.y / squareside) * squareside + squareside;
// 		end.x = start.x - (end.y - start.y) / tan(angle);
// 		delta_ray.y = squareside;
// 		delta_ray.x = - delta_ray.y / tan(angle);
// 	}
// 	while (!reached_wall)
// 	{
// 		ft_printf("Y = %d, X += %d\n", (int)((end.y) / squareside), (int)((end.x) / squareside));
// 		if (ft_strchr("12", mywin->params.map[(int)((end.y) / squareside)][(int)((end.x) / squareside)]))
// 			reached_wall = 1;
// 		else
// 		{
// 			end.x += delta_ray.x;
// 			end.y += delta_ray.y;
// 		}
// 	}
// 	return (end);
// }

void	drawRays(t_vars *mywin)
{
	float angle;
	t_point start;
	t_point h_end;

	angle = mywin->player.angle;
	start.x = mywin->player.x_pos;
	start.y = mywin->player.y_pos;
	h_end = getHorRay(mywin, start, angle);
	// v_end = getVerRay(mywin, start, angle);
	draw_line(&mywin->player_img, start, h_end, 0x0000FF00);
}
