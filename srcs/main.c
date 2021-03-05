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

void	init_cub2(t_vars *mywin)
{
	mywin->s_text.img = mlx_xpm_file_to_image(mywin->mlx,
		mywin->params.so_path, &mywin->s_text.width, &mywin->s_text.height);
	mywin->s_text.addr = mlx_get_data_addr(mywin->s_text.img,
		&mywin->s_text.bits_per_pixel, &mywin->s_text.line_length,
		&mywin->s_text.endian);
	mywin->e_text.img = mlx_xpm_file_to_image(mywin->mlx,
		mywin->params.ea_path, &mywin->e_text.width, &mywin->e_text.height);
	mywin->e_text.addr = mlx_get_data_addr(mywin->e_text.img,
		&mywin->e_text.bits_per_pixel, &mywin->e_text.line_length,
		&mywin->e_text.endian);
	mywin->w_text.img = mlx_xpm_file_to_image(mywin->mlx,
		mywin->params.we_path, &mywin->w_text.width, &mywin->w_text.height);
	mywin->w_text.addr = mlx_get_data_addr(mywin->w_text.img,
		&mywin->w_text.bits_per_pixel, &mywin->w_text.line_length,
		&mywin->w_text.endian);
	mywin->sprite.img = mlx_xpm_file_to_image(mywin->mlx,
		mywin->params.sp_path, &mywin->sprite.width, &mywin->sprite.height);
	mywin->sprite.addr = mlx_get_data_addr(mywin->sprite.img,
		&mywin->sprite.bits_per_pixel, &mywin->sprite.line_length,
		&mywin->sprite.endian);
	mywin->norms = (float*)ft_calloc(mywin->params.res_x, sizeof(float));
	mywin->i = -1;
	fill_window(mywin, &mywin->img, 0x00808080);
	put_map(mywin, &mywin->img);
}

void	init_cub(t_vars *mywin)
{
	mywin->move.x = 0;
	mywin->move.y = 0;
	mywin->move.rot = 0;
	mywin->win = (void*)NULL;
	mywin->img.img = mlx_new_image(mywin->mlx, mywin->params.res_x,
		mywin->params.res_y);
	mywin->img.addr = mlx_get_data_addr(mywin->img.img,
	&mywin->img.bits_per_pixel, &mywin->img.line_length, &mywin->img.endian);
	mywin->player_img.img = mlx_new_image(mywin->mlx, mywin->params.res_x,
		mywin->params.res_y);
	mywin->player_img.addr = mlx_get_data_addr(mywin->player_img.img,
		&mywin->player_img.bits_per_pixel, &mywin->player_img.line_length,
		&mywin->player_img.endian);
	mywin->fps_img.img = mlx_new_image(mywin->mlx, mywin->params.res_x,
		mywin->params.res_y);
	mywin->fps_img.addr = mlx_get_data_addr(mywin->fps_img.img,
		&mywin->fps_img.bits_per_pixel, &mywin->fps_img.line_length,
		&mywin->fps_img.endian);
	mywin->n_text.img = mlx_xpm_file_to_image(mywin->mlx,
		mywin->params.no_path, &mywin->n_text.width, &mywin->n_text.height);
	mywin->n_text.addr = mlx_get_data_addr(mywin->n_text.img,
		&mywin->n_text.bits_per_pixel, &mywin->n_text.line_length,
		&mywin->n_text.endian);
	init_cub2(mywin);
}

int		err_capt(t_vars *mywin, int argc, char **argv)
{
	if (mywin->params.err)
	{
		ft_printf("Error\n%s", mywin->params.err);
		free(mywin->params.err);
		return (exit_hook(mywin));
	}
	else
	{
		init_cub(mywin);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
		{
			draw_rays(mywin);
			mk_bmp(mywin->fps_img.addr, mywin->params.res_y,
				mywin->params.res_x);
			return (exit_hook(mywin));
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_vars	mywin;

	if (argc == 2 || argc == 3)
	{
		mywin.mlx = mlx_init();
		mywin.img.addr = 0;
		mywin.params = parse_file(argv[1]);
		if (!mywin.params.err)
			check_error(&mywin);
		err_capt(&mywin, argc, argv);
		mywin.win = mlx_new_window(mywin.mlx, mywin.params.res_x,
			mywin.params.res_y, "cub3D");
		mlx_hook(mywin.win, X_EVENT_KEY_PRESS, 1L, &key_press, &mywin);
		mlx_hook(mywin.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &mywin);
		mlx_hook(mywin.win, X_EVENT_EXIT, 1L << 17, &exit_hook, &mywin);
		mlx_loop_hook(mywin.mlx, do_stuff, &mywin);
		mlx_loop(mywin.mlx);
	}
	else
		ft_printf("Invalid argument\n");
	return (0);
}
