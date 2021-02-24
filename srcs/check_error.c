/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:33:52 by rgilles           #+#    #+#             */
/*   Updated: 2021/02/19 20:34:04 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_error(t_vars *mywin)
{
	int	max_x;
	int	max_y;

	if (mywin->params.err)
		return ;
	if (!(mywin->params.res_x && mywin->params.res_y))
		mywin->params.err = "Resolution unset.\n";
	if (!(mywin->params.so_path && mywin->params.no_path && mywin->params.ea_path
		&& mywin->params.we_path && mywin->params.sp_path))
		mywin->params.err = "Texture paths unset.\n";
	if (!(mywin->params.floor_col && mywin->params.ceilg_col))
		mywin->params.err = "Background colours unset.\n";
	if (!mywin->params.map)
		mywin->params.err = "No map\n";
	mlx_get_screen_size(mywin->mlx, &max_x, &max_y);
	if (mywin->params.res_x > max_x || mywin->params.res_y > max_y)
	{
		ft_printf("Warning : the current screen resolution is inferior to the one specified.");
		ft_printf("Falling back to current resolution\n");
		mywin->params.res_x = max_x;
		mywin->params.res_y = max_y;
	}
}