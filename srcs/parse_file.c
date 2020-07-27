/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:01:09 by rgilles           #+#    #+#             */
/*   Updated: 2020/07/24 15:01:12 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_params	parse_file(char *path)
{
	int			fd;
	char		*line;
	t_params	params;
	int			len_x;

	if(open())
	while (get_next_line(fd, &line) >= 0)
	{
		if(line[0] == 'R')
		{
			len_x = 0;
			params.res_x = ft_atoi(line[1]);
			while ()
			params.res_y = ft_atoi(line[2 + len_x]);
		}
	}
}
