/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:45:53 by rgilles           #+#    #+#             */
/*   Updated: 2021/02/26 15:45:56 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		is_full_border(t_vars *mywin, t_coord curr, t_coord start, int prev)
{
	ft_printf("Checking %d, %d\n", curr.x, curr.y);
	if (prev && curr.x == start.x && curr.y == start.y)
		return (1);
	if (curr.x - 1 >= 0
		&& mywin->params.map[curr.y][curr.x - 1] == '1' && prev != 2)
	{
		(curr.x)--;
		if (is_full_border(mywin, curr, start, -2) == 1)
			return (1);
		(curr.x)++;
	}
	if (curr.y + 1 < mywin->params.map_y
		&& mywin->params.map[curr.y + 1][curr.x] == '1' && prev != -1)
	{
		(curr.y)++;
		if (is_full_border(mywin, curr, start, 1) == 1)
			return (1);
		(curr.y)--;
	}
	if (curr.x + 1 < mywin->params.map_x
		&& mywin->params.map[curr.y][curr.x + 1] == '1' && prev != -2)
	{
		(curr.x)++;
		if (is_full_border(mywin, curr, start, 2) == 1)
			return (1);
		(curr.x)--;
	}
	if (curr.y - 1 >= 0
		&& mywin->params.map[curr.y - 1][curr.x] == '1' && prev != 1)
	{
		(curr.y)--;
		if (is_full_border(mywin, curr, start, -1) == 1)
			return (1);
		(curr.y)++;
	}
	return (0);
}

void	border_closure(t_vars *mywin, int x, int y)
{
	t_coord	start_wall;

	while (--y >= 0)
		if (mywin->params.map[y][x] == '1')
		{
			start_wall.x = x;
			start_wall.y = y;
			if (is_full_border(mywin, start_wall, start_wall, 0))
				return ;
		}
	mywin->params.err = ft_strdup("Map isn't closed.\n");
}

void	check_map_content(t_vars *mywin)
{
	int	i;
	int	j;
	int x;
	int y;

	i = -1;
	y = -1;
	x = -1;
	while (mywin->params.map[++i] && (j = -1))
		while (mywin->params.map[i][++j])
			if (ft_strchr("ENWS", mywin->params.map[i][j]))
			{
				if (x == -1)
				{
					x = j;
					y = i;
					ft_printf("player detected at %d, %d\n", x, y);
				}
				else
				{
					mywin->params.err = ft_strdup("Multiple players on map.\n");
					return ;
				}
			}
	border_closure(mywin, x, y + 1);
}

void	check_error(t_vars *mywin)
{
	int	max_x;
	int	max_y;

	if (mywin->params.err)
		return ;
	else if (!(mywin->params.res_x && mywin->params.res_y))
		mywin->params.err = ft_strdup("Resolution unset.\n");
	else if (!(mywin->params.so_path && mywin->params.no_path
		&& mywin->params.ea_path && mywin->params.we_path
		&& mywin->params.sp_path))
		mywin->params.err = ft_strdup("Texture paths unset.\n");
	else if (!(mywin->params.floor_col && mywin->params.ceilg_col))
		mywin->params.err = ft_strdup("Background colours unset.\n");
	else if (!mywin->params.map)
		mywin->params.err = ft_strdup("No map\n");
	mlx_get_screen_size(mywin->mlx, &max_x, &max_y);
	if (mywin->params.res_x > max_x || mywin->params.res_y > max_y)
	{
		ft_printf("Warning : current screen resolution inferior to specified.");
		ft_printf("Falling back to current resolution\n");
		mywin->params.res_x = max_x;
		mywin->params.res_y = max_y;
	}
	check_map_content(mywin);
}
