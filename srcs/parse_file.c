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

int			get_fccol(char *line)
{
	int	toret;
	int	i;

	toret = 0xFF << 24 | ft_atoi(line + 1) << 16;
	i = 2;
	while (ft_isdigit(line[i++]))
		;
	toret = toret | ft_atoi(line + i) << 8;
	while (ft_isdigit(line[i++]))
		;
	toret = toret | ft_atoi(line + i) << 0;
	return (toret);
}

t_params	parse_file(char *path)
{
	int			fd;
	char		*line;
	t_params	params;
	int			i;

		fd = open(path, O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			if(line[0] == 'R')
			{
				params.res_x = ft_atoi(line + 1);
				i = 2;
				while (ft_isdigit(line[i]))
					i++;
				while (ft_isspace(line[i]))
					i++;
				params.res_y = ft_atoi(line + i);
			}
			if(line[0] == 'F')
				params.floor_col = get_fccol(line);
			if(line[0] == 'C')
				params.ceil_col = get_fccol(line);
		}
	return params;
}
