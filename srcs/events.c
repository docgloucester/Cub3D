/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 00:26:49 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/04 00:26:52 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		refresh(t_vars *mywin)
{
	t_img	temp_img;

	temp_img.img = mlx_new_image(mywin->mlx, mywin->params.res_x / 4,
		mywin->params.res_y / 4);
	temp_img.addr = mlx_get_data_addr(temp_img.img, &temp_img.bits_per_pixel,
		&temp_img.line_length, &temp_img.endian);
	mlx_merge_img(mywin, &temp_img, &mywin->img, &mywin->player_img);
	mlx_put_image_to_window(mywin->mlx, mywin->win, mywin->fps_img.img, 0, 0);
	mlx_put_image_to_window(mywin->mlx, mywin->win, temp_img.img, 0, 0);
	mlx_destroy_image(mywin->mlx, temp_img.img);
	return (0);
}

int		key_press(int keycode, t_vars *mywin)
{
	if (keycode == UP_KEY)
		mywin->move.y = 1;
	if (keycode == DOWN_KEY)
		mywin->move.y = -1;
	if (keycode == LEFT_KEY)
		mywin->move.x = 1;
	if (keycode == RIGHT_KEY)
		mywin->move.x = -1;
	if (keycode == DPAD_LEFT)
		mywin->move.rot = -1;
	if (keycode == DPAD_RIGHT)
		mywin->move.rot = 1;
	return (0);
}

int		key_release(int keycode, t_vars *mywin)
{
	if (keycode == UP_KEY || keycode == DOWN_KEY)
		mywin->move.y = 0;
	if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		mywin->move.x = 0;
	if (keycode == DPAD_LEFT || keycode == DPAD_RIGHT)
		mywin->move.rot = 0;
	if (keycode == ESC_KEY)
		return (exit_hook(mywin));
	return (0);
}

int		check_collisions(t_vars *mywin, float dx, float dy, int squareside)
{
	int i;

	i = 0;
	while (i <= 10 &&
		!(ft_strchr("12", mywin->params.map[(int)((mywin->player.y_pos +
			(float)i * 0.2f * dy) / (float)squareside)]
			[(int)((mywin->player.x_pos +
			(float)i * 0.2f * dx) / (float)squareside)])))
		i++;
	return (i);
}

int		do_stuff(t_vars *mywin)
{
	int		squareside;
	float	dx;
	float	dy;

	squareside = get_square_side(mywin);
	if (mywin->move.x || mywin->move.y)
	{
		dx = (float)squareside / 4.0f * (mywin->player.dx * mywin->move.y
			+ mywin->player.dy * mywin->move.x);
		dy = (float)squareside / 4.0f * (mywin->player.dy * mywin->move.y
			- mywin->player.dx * mywin->move.x);
		if (check_collisions(mywin, dx, dy, squareside) == 11)
		{
			mywin->player.x_pos += dx;
			mywin->player.y_pos += dy;
		}
	}
	if (mywin->move.rot)
		chg_angle(&mywin->player, mywin->player.angle - 0.15 * mywin->move.rot);
	fill_window(mywin, &mywin->player_img, 0xFFFFFFFF);
	place_player(mywin, 0x00FF0000);
	mywin->i = -1;
	draw_rays(mywin);
	refresh(mywin);
	return (0);
}
