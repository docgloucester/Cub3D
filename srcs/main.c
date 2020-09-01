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

void	fill_window(t_vars *mywin, int colour)
{
	int 	x;
	int 	y;
	t_data	img;

	img.img = mlx_new_image(mywin->mlx, mywin->params.res_x, mywin->params.res_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = -1;
	while (++y < mywin->params.res_y)
	{
		x = -1;
		while (++x < mywin->params.res_x)
			my_pixelput(&img, x, y, colour);
	}
	mlx_put_image_to_window(mywin->mlx, mywin->win, img.img, 0, 0);
}

int		key_function(int key, t_vars *mywin)
{
	ft_printf("Key n.%d", key);
	if (key == ESC_KEY)
	{
		mlx_destroy_window(mywin->mlx, mywin->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int		infocus_function(t_vars *mywin)
{
	fill_window(mywin, 0x0000FF00);
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
		ft_printf("X = %d x %d\nFloor colour = %X\nNorth Path = %s\n", mywin.params.res_x, mywin.params.res_y,
			mywin.params.ceilg_col, mywin.params.no_path);
		mywin.win = mlx_new_window(mywin.mlx, mywin.params.res_x, mywin.params.res_y, "Hello world!");
		fill_window(&mywin, 0x00FF0000);
		mlx_key_hook(mywin.win, key_function, &mywin);
		mlx_hook(mywin.win, 9, 1L<<21, infocus_function, &mywin);
		mlx_loop(mywin.mlx);
	}
	else
	{
		(void)mywin;
		ft_printf("Invalid argument\n");
	}
	return (0);
}
