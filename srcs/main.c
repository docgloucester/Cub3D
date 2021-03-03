/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:36:18 by rgilles           #+#    #+#             */
/*   Updated: 2020/07/24 12:36:20 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		refresh(t_vars *mywin)
{
	t_img	temp_img;

	temp_img.img = mlx_new_image(mywin->mlx, mywin->params.res_x / 4, mywin->params.res_y / 4);
	temp_img.addr = mlx_get_data_addr(temp_img.img, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	mlx_merge_img(mywin, &temp_img, &mywin->img, &mywin->player_img);
	mlx_put_image_to_window(mywin->mlx, mywin->win, mywin->fps_img.img, 0, 0);
	mlx_put_image_to_window(mywin->mlx, mywin->win, temp_img.img, 0, 0);
	mlx_destroy_image(mywin->mlx, temp_img.img);
	return (0);
}

int		exit_hook(t_vars *mywin)
{
	if (mywin->img.addr)
	{
		mlx_destroy_image(mywin->mlx, mywin->img.img);
		mlx_destroy_image(mywin->mlx, mywin->player_img.img);
		mlx_destroy_image(mywin->mlx, mywin->fps_img.img);
		mlx_destroy_image(mywin->mlx, mywin->n_text.img);
		mlx_destroy_image(mywin->mlx, mywin->s_text.img);
		mlx_destroy_image(mywin->mlx, mywin->e_text.img);
		mlx_destroy_image(mywin->mlx, mywin->w_text.img);
		mlx_destroy_image(mywin->mlx, mywin->sprite.img);
		if (mywin->win)
			mlx_destroy_window(mywin->mlx, mywin->win);
		free(mywin->norms);
	}
	free(mywin->params.no_path);
	free(mywin->params.so_path);
	free(mywin->params.ea_path);
	free(mywin->params.we_path);
	free(mywin->params.sp_path);
	if (mywin->params.map)
		free_split(mywin->params.map);
	mlx_destroy_display(mywin->mlx);
	free(mywin->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int		key_press(int keycode, t_vars *mywin)
{
	if (keycode == UP_KEY)
		mywin->move.y = 1;
	if (keycode == DOWN_KEY)
		mywin->move.y = - 1;
	if (keycode == LEFT_KEY)
		mywin->move.x = 1;
	if (keycode == RIGHT_KEY)
		mywin->move.x = - 1;
	if (keycode == DPAD_LEFT)
		mywin->move.rot = - 1;
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
		!(ft_strchr("12", mywin->params.map[(int)((mywin->player.y_pos + (float)i * 0.2f * dy) / (float)squareside)]
			[(int)((mywin->player.x_pos + (float)i * 0.2f * dx) / (float)squareside)])))
		i++;
	return (i);
}

int		do_stuff(t_vars *mywin)
{
	int		squareside;
	float	dx;
	float	dy;
	int		i;

	squareside = get_square_side(mywin);
	if (mywin->move.x || mywin->move.y)
	{
		dx = (float)squareside / 4.0f * (mywin->player.dx * mywin->move.y
			+ mywin->player.dy * mywin->move.x);
		dy = (float)squareside / 4.0f * (mywin->player.dy * mywin->move.y
			- mywin->player.dx * mywin->move.x);
		i = check_collisions(mywin, dx, dy, squareside);
		if (i == 11)
		{
			mywin->player.x_pos += dx;
			mywin->player.y_pos += dy;
		}
	}
	if (mywin->move.rot)
		change_angle(&mywin->player, mywin->player.angle - 0.15 * mywin->move.rot);
	fill_window(mywin, &mywin->player_img, 0xFFFFFFFF);
	place_player(mywin, 0x00FF0000);
	draw_rays(mywin);
	refresh(mywin);
	return (0);
}

int		main(int argc, char **argv)
{
	t_vars	mywin;

	if (argc == 2 || argc == 3)
	{
		mywin.mlx = mlx_init();
		mywin.params = parse_file(argv[1]);
		if (!mywin.params.err)
			check_error(&mywin);
		mywin.img.addr = 0;
		if (mywin.params.err)
		{
			ft_printf("Error\n%s", mywin.params.err);
			free(mywin.params.err);
			return (exit_hook(&mywin));
		}
		mywin.move.x = 0;
		mywin.move.y = 0;
		mywin.move.rot = 0;
		mywin.norms = (float*)ft_calloc(mywin.params.res_x, sizeof(float));
		mywin.img.img = mlx_new_image(mywin.mlx, mywin.params.res_x, mywin.params.res_y);
		mywin.img.addr = mlx_get_data_addr(mywin.img.img, &mywin.img.bits_per_pixel, &mywin.img.line_length, &mywin.img.endian);
		mywin.player_img.img = mlx_new_image(mywin.mlx, mywin.params.res_x, mywin.params.res_y);
		mywin.player_img.addr = mlx_get_data_addr(mywin.player_img.img, &mywin.player_img.bits_per_pixel, &mywin.player_img.line_length, &mywin.player_img.endian);
		mywin.fps_img.img = mlx_new_image(mywin.mlx, mywin.params.res_x, mywin.params.res_y);
		mywin.fps_img.addr = mlx_get_data_addr(mywin.fps_img.img, &mywin.fps_img.bits_per_pixel, &mywin.fps_img.line_length, &mywin.fps_img.endian);
		mywin.n_text.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.no_path, &mywin.n_text.width, &mywin.n_text.height);
		mywin.n_text.addr = mlx_get_data_addr(mywin.n_text.img, &mywin.n_text.bits_per_pixel, &mywin.n_text.line_length, &mywin.n_text.endian);
		mywin.s_text.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.so_path, &mywin.s_text.width, &mywin.s_text.height);
		mywin.s_text.addr = mlx_get_data_addr(mywin.s_text.img, &mywin.s_text.bits_per_pixel, &mywin.s_text.line_length, &mywin.s_text.endian);
		mywin.e_text.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.ea_path, &mywin.e_text.width, &mywin.e_text.height);
		mywin.e_text.addr = mlx_get_data_addr(mywin.e_text.img, &mywin.e_text.bits_per_pixel, &mywin.e_text.line_length, &mywin.e_text.endian);
		mywin.w_text.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.we_path, &mywin.w_text.width, &mywin.w_text.height);
		mywin.w_text.addr = mlx_get_data_addr(mywin.w_text.img, &mywin.w_text.bits_per_pixel, &mywin.w_text.line_length, &mywin.w_text.endian);
		mywin.sprite.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.sp_path, &mywin.sprite.width, &mywin.sprite.height);
		mywin.sprite.addr = mlx_get_data_addr(mywin.sprite.img, &mywin.sprite.bits_per_pixel, &mywin.sprite.line_length, &mywin.sprite.endian);
		build_image(&mywin, &mywin.img);
		mywin.win = (void*)NULL;
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
		{
			create_bmp(mywin.fps_img.addr, mywin.params.res_y, mywin.params.res_x);
			return (exit_hook(&mywin));
		}
		mywin.win = mlx_new_window(mywin.mlx, mywin.params.res_x, mywin.params.res_y, "Cub3D");
		mlx_hook(mywin.win, X_EVENT_KEY_PRESS, 1L, &key_press, &mywin);
		mlx_hook(mywin.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &mywin);
		mlx_hook(mywin.win, X_EVENT_EXIT, 1L << 17, &exit_hook, &mywin);
		mlx_loop_hook(mywin.mlx, do_stuff, &mywin);
		mlx_loop(mywin.mlx);
	}
	else
	{
		(void)mywin;
		ft_printf("Invalid argument\n");
	}
	return (0);
}
