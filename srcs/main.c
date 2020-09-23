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
	temp_img.img = mlx_new_image(mywin->mlx, mywin->params.res_x / 4 , mywin->params.res_y / 4);
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
	ft_printf ("%d x %d\n", mywin->params.mapX, mywin->params.mapY);
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

int		key_function(int key, t_vars *mywin)
{
	int		squareside;
	float	dx;
	float	dy;

	squareside = get_square_side(mywin);
	if (key == LEFT_KEY || key == RIGHT_KEY || key == UP_KEY || key == DOWN_KEY)
	{
		dx = get_square_side(mywin) / 2 * (mywin->player.dx * ((key == UP_KEY) - (key == DOWN_KEY)) + mywin->player.dy * ((key == LEFT_KEY) - (key == RIGHT_KEY)));
		dy = get_square_side(mywin) / 2 * (mywin->player.dy * ((key == UP_KEY) - (key == DOWN_KEY)) - mywin->player.dx * ((key == LEFT_KEY) - (key == RIGHT_KEY)));
		if (!ft_strchr("12", mywin->params.map[(int)((mywin->player.y_pos + 2 * dy) / squareside)][(int)((mywin->player.x_pos + 2 * dx) / squareside)]))
		{
			mywin->player.x_pos += dx;
			mywin->player.y_pos += dy;
		}
	}
	else if (key == DPAD_LEFT || key == DPAD_RIGHT)
	{
		fill_window(mywin, &mywin->player_img, 0xFFFFFFFF);
		change_angle(&mywin->player, mywin->player.angle - 0.1 * ((key == DPAD_RIGHT) - (key == DPAD_LEFT)));
	}
	else if (key == ESC_KEY)
	{
		mlx_destroy_window(mywin->mlx, mywin->win);
		exit(EXIT_SUCCESS);
	}
	fill_window(mywin, &mywin->player_img, 0xFFFFFFFF);
	place_player(mywin, 0x00FF0000);
	drawRays(mywin);
	draw_player_dir(mywin, 0x00FF0000);
	refresh(mywin);
	return (0);
}

int		infocus_function(t_vars *mywin)
{
	refresh(mywin);
	return (0);
}

int		main(int argc, char **argv)
{
	t_vars		mywin;

	if (argc == 2)
	{
		mywin.mlx = mlx_init();
		mlx_do_key_autorepeaton(mywin.mlx);
		mywin.params = parse_file(argv[1]);
		if (mywin.params.err)
		{
			ft_printf("Error\n%s", mywin.params.err);
			exit(EXIT_FAILURE);
		}
		print_map(&mywin);
		mywin.win = mlx_new_window(mywin.mlx, mywin.params.res_x, mywin.params.res_y, "Hello world!");
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
		fill_window(&mywin, &mywin.player_img, 0xFFFFFFFF);
		build_image(&mywin, &mywin.img);
		refresh(&mywin);
		mlx_key_hook(mywin.win, key_function, &mywin);
		mlx_hook(mywin.win, 9, 1L<<21, infocus_function, &mywin);
		//mlx_loop_hook(mywin.mlx, refresh, &mywin);
		mlx_loop(mywin.mlx);
	}
	else
	{
		(void)mywin;
		ft_printf("Invalid argument\n");
	}
	return (0);
}
