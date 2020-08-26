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

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	t_params	params;
	t_data		img;
	t_player	player;

	if (argc == 2)
	{
		mlx = mlx_init();
		params = parse_file(argv[1]);
		if (params.err)
		{
			ft_printf("Error\n%s", params.err);
			exit(EXIT_FAILURE);
		}
		ft_printf("X = %d\n", params.res_x);
		ft_printf("Y = %d\n", params.res_y);
		ft_printf("Floor colour = %X\n", params.floor_col);
		ft_printf("Ceiling colour = %X\n", params.ceilg_col);
		ft_printf("North Path = %s\n", params.no_path);
		player.x_pos = 135;
		player.y_pos = 256;
		win = mlx_new_window(mlx, params.res_x, params.res_y, "Hello world!");
		ft_printf("hello\n");
		img.img = mlx_new_image(mlx, params.res_x, params.res_y);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		my_pixelput(&img, player.x_pos, player.y_pos, 0x00FF0000);
		mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		mlx_loop(mlx);
	}
	else
	{
		(void)win;
		ft_printf("Invalid argument\n");
	}
	return (0);
}
