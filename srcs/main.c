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

void	print_map(t_vars *mywin)
{
	int	i;

	i = 0;
	ft_printf ("%d x %d\n", mywin->params.mapX, mywin->params.mapY);
	while (mywin->params.map[i])
		ft_printf("%s\n", mywin->params.map[i++]);
}

int		key_function(int key, t_vars *mywin)
{
	ft_printf("Key n.%d", key);
	if (key == 0x77 || key == 0x61 || key == 0x73 || key == 0x64)
	{
		place_player(mywin, 0x00808080);
		mywin->player.x_pos += (key == 0x64);
		mywin->player.x_pos -= (key == 0x61);
		place_player(mywin, 0x00FF0000);
		mlx_put_image_to_window(mywin->mlx, mywin->win, mywin->img.img, 0, 0);
	}
	else if (key == ESC_KEY)
	{
		mlx_destroy_window(mywin->mlx, mywin->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int		infocus_function(t_vars *mywin)
{
	build_image(mywin, &mywin->img);
	mlx_put_image_to_window(mywin->mlx, mywin->win, mywin->img.img, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_vars		mywin;

	if (argc == 2)
	{
		mywin.mlx = mlx_init();
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
		build_image(&mywin, &mywin.img);
		mlx_put_image_to_window(mywin.mlx, mywin.win, mywin.img.img, 0, 0);
		mlx_key_hook(mywin.win, key_function, &mywin);
		mlx_hook(mywin.win, 9, 1L<<21, infocus_function, &mywin);
		mlx_do_key_autorepeaton(mywin.mlx);
		mlx_loop(mywin.mlx);
	}
	else
	{
		(void)mywin;
		ft_printf("Invalid argument\n");
	}
	return (0);
}
