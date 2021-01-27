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

	mlx_put_image_to_window(mywin->mlx, mywin->win, mywin->fps_img.img, 0, 0);
	temp_img.img = mlx_new_image(mywin->mlx, mywin->params.res_x / 4, mywin->params.res_y / 4);
	temp_img.addr = mlx_get_data_addr(temp_img.img, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	mlx_merge_img(mywin, &temp_img, &mywin->img, &mywin->player_img);
	mlx_put_image_to_window(mywin->mlx, mywin->win, temp_img.img, 0, 0);
	mlx_destroy_image(mywin->mlx, temp_img.img);
	return (0);
}

void	print_map(t_vars *mywin)
{
	int	i;

	i = 0;
	ft_printf ("%d x %d\n", mywin->params.map_x, mywin->params.map_y);
	while (mywin->params.map[i])
		ft_printf("%s\n", mywin->params.map[i++]);
}

void	draw_player_dir(t_vars *mywin, int col)
{
	t_point	start;
	t_point	end;

	start.x = mywin->player.x_pos;
	start.y = mywin->player.y_pos;
	end.x = mywin->player.x_pos + get_square_side(mywin) * mywin->player.dx;
	end.y = mywin->player.y_pos + get_square_side(mywin) * mywin->player.dy;
	draw_line(mywin, start, end, col);
}

int		check_collisions(t_vars *mywin, float dx, float dy, int squareside)
{
	int i;

	i = 0;
	while (i < 10 &&
			!(
			   ft_strchr("12", mywin->params.map[(int)((mywin->player.y_pos       + (float)i * 0.2 * dy) / (float)squareside)][(int)((mywin->player.x_pos       + (float)i * 0.2 * dx) / (float)squareside)])
			// || ft_strchr("12", mywin->params.map[(int)((mywin->player.y_pos + 0.1 + (float)i * 0.2 * dy) / (float)squareside)][(int)((mywin->player.x_pos + 0.1 + (float)i * 0.2 * dx) / (float)squareside)])
			// || ft_strchr("12", mywin->params.map[(int)((mywin->player.y_pos + 0.1 + (float)i * 0.2 * dy) / (float)squareside)][(int)((mywin->player.x_pos       + (float)i * 0.2 * dx) / (float)squareside)])
			// || ft_strchr("12", mywin->params.map[(int)((mywin->player.y_pos       + (float)i * 0.2 * dy) / (float)squareside)][(int)((mywin->player.x_pos + 0.1 + (float)i * 0.2 * dx) / (float)squareside)])
			 )
			)
		i += 1;
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
		dx = get_square_side(mywin) / 4 * (mywin->player.dx * mywin->move.y
			+ mywin->player.dy * mywin->move.x);
		dy = get_square_side(mywin) / 4 * (mywin->player.dy * mywin->move.y
			- mywin->player.dx * mywin->move.x);
		i = check_collisions(mywin, dx, dy, squareside);
		if (i == 10)
		{
			mywin->player.x_pos += dx;
			mywin->player.y_pos += dy;
		}
	}
	if (mywin->move.rot)
	{
		fill_window(mywin, &mywin->player_img, 0xFFFFFFFF);
		change_angle(&mywin->player, mywin->player.angle - 0.15 * mywin->move.rot);
	}
	fill_window(mywin, &mywin->player_img, 0xFFFFFFFF);
	place_player(mywin, 0x00FF0000);
	draw_rays(mywin);
	draw_player_dir(mywin, 0x00FF0000);
	refresh(mywin);
	return (0);
}

int		infocus_function(t_vars *mywin)
{
	refresh(mywin);
	return (0);
}

int		exit_hook(t_vars *mywin)
{
	mlx_destroy_window(mywin->mlx, mywin->win);
	free(mywin->sprites_array);
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

int		main(int argc, char **argv)
{
	t_vars		mywin;

	if (argc == 2 || argc == 3)
	{
		mywin.mlx = mlx_init();
		mywin.params = parse_file(argv[1]);
		mywin.sprites_array = (float*)ft_calloc(2 * mywin.params.res_x, sizeof(float));
		mywin.norms_array = (float*)ft_calloc(mywin.params.res_x, sizeof(float));
		mywin.move.x = 0;
		mywin.move.y = 0;
		mywin.move.rot = 0;
		if (mywin.params.err)
		{
			ft_printf("Error\n%s", mywin.params.err);
			exit(EXIT_FAILURE);
		}
		print_map(&mywin);
		mywin.win = mlx_new_window(mywin.mlx, mywin.params.res_x, mywin.params.res_y, "Cub3D");
		mywin.img.img = mlx_new_image(mywin.mlx, mywin.params.res_x, mywin.params.res_y);
		mywin.img.addr = mlx_get_data_addr(mywin.img.img, &mywin.img.bits_per_pixel, &mywin.img.line_length, &mywin.img.endian);
		mywin.player_img.img = mlx_new_image(mywin.mlx, mywin.params.res_x, mywin.params.res_y);
		mywin.player_img.addr = mlx_get_data_addr(mywin.player_img.img, &mywin.player_img.bits_per_pixel, &mywin.player_img.line_length, &mywin.player_img.endian);
		mywin.fps_img.img = mlx_new_image(mywin.mlx, mywin.params.res_x, mywin.params.res_y);
		mywin.fps_img.addr = mlx_get_data_addr(mywin.fps_img.img, &mywin.fps_img.bits_per_pixel, &mywin.fps_img.line_length, &mywin.fps_img.endian);
		mywin.n_text.img.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.no_path, &mywin.n_text.img.width, &mywin.n_text.img.height);
		mywin.n_text.img.addr = mlx_get_data_addr(mywin.n_text.img.img, &mywin.n_text.img.bits_per_pixel, &mywin.n_text.img.line_length, &mywin.n_text.img.endian);
		mywin.s_text.img.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.so_path, &mywin.s_text.img.width, &mywin.s_text.img.height);
		mywin.s_text.img.addr = mlx_get_data_addr(mywin.s_text.img.img, &mywin.s_text.img.bits_per_pixel, &mywin.s_text.img.line_length, &mywin.s_text.img.endian);
		mywin.e_text.img.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.ea_path, &mywin.e_text.img.width, &mywin.e_text.img.height);
		mywin.e_text.img.addr = mlx_get_data_addr(mywin.e_text.img.img, &mywin.e_text.img.bits_per_pixel, &mywin.e_text.img.line_length, &mywin.e_text.img.endian);
		mywin.w_text.img.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.we_path, &mywin.w_text.img.width, &mywin.w_text.img.height);
		mywin.w_text.img.addr = mlx_get_data_addr(mywin.w_text.img.img, &mywin.w_text.img.bits_per_pixel, &mywin.w_text.img.line_length, &mywin.w_text.img.endian);
		mywin.sprite.img.img = mlx_xpm_file_to_image(mywin.mlx, mywin.params.sp_path, &mywin.sprite.img.width, &mywin.sprite.img.height);
		mywin.sprite.img.addr = mlx_get_data_addr(mywin.sprite.img.img, &mywin.sprite.img.bits_per_pixel, &mywin.sprite.img.line_length, &mywin.sprite.img.endian);
		fill_window(&mywin, &mywin.player_img, 0xFFFFFFFF);
		build_image(&mywin, &mywin.img);
		refresh(&mywin);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
		{
			create_bmp(mywin.fps_img.addr, mywin.params.res_y, mywin.params.res_x);
			return (exit_hook(&mywin));
		}
		ft_printf("%d\n", get_square_side(&mywin));
		mlx_hook(mywin.win, X_EVENT_KEY_PRESS, 1L, &key_press, &mywin);
		mlx_hook(mywin.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &mywin);
		mlx_hook(mywin.win, X_EVENT_EXIT, 0, &exit_hook, &mywin);
		mlx_hook(mywin.win, 9, 1L << 21, infocus_function, &mywin);
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
