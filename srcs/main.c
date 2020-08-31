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

void	fill_window(void **mlx, void **win, t_params *params, int colour)
{
	int 	x;
	int 	y;
	t_data	img;

	img.img = mlx_new_image(*mlx, params->res_x, params->res_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = -1;
	while (++y < params->res_y)
	{
		x = -1;
		while (++x < params->res_x)
			my_pixelput(&img, x, y, colour);
	}
	mlx_put_image_to_window(*mlx, *win, img.img, 0, 0);
}

int		main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	t_params	params;

	if (argc == 2)
	{
		mlx = mlx_init();
		params = parse_file(argv[1]);
		if (params.err)
		{
			ft_printf("Error\n%s", params.err);
			exit(EXIT_FAILURE);
		}
		ft_printf("X = %d x %d\nFloor colour = %X\nNorth Path = %s\n", params.res_x, params.res_y,
			params.ceilg_col, params.no_path);
		win = mlx_new_window(mlx, params.res_x, params.res_y, "Hello world!");
		fill_window(&mlx, &win, &params, 0x00FF0000);
		mlx_loop(mlx);
	}
	else
	{
		(void)win;
		ft_printf("Invalid argument\n");
	}
	return (0);
}
