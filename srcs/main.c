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

	int i;

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
		win = mlx_new_window(mlx, params.res_x, params.res_y, "Hello world!");
		i = 0;
		// while(params.map[i])
		// {
		// 	ft_printf("Line n. %d : %s\n", i, params.map[i]);
		// 	free(params.map[i++]);
		// }
		// free(params.map);
		mlx_loop(mlx);
	}
	else
	{
		(void)win;
		ft_printf("Invalid argument\n");
	}
	return (0);
}
