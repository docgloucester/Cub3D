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

void		get_res(t_params *params, char *line)
{
	int	i;

	params->res_x = ft_atoi(line + 1);
	i = 2;
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	params->res_y = ft_atoi(line + i);
}

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

char		*get_path(char *line)
{
	int		i;

	i = 0;
	if (ft_isspace(*line))
	{
		while (ft_isspace(line[i]))
			i++;
		return (ft_strdup(line + i));
	}
	return (NULL);
}

void		deal_map(t_params *params, char	**line, int fd)
{
	int	i;

	i = 1;
	params->map = (char**)malloc(i * sizeof(char*));
	params->map[0] = ft_strdup(*line);
	get_next_line(fd, line);
	while (ft_split(*line, ' ')[0][0] == '1')
	{
		i++;
		params->map = ft_realloc(params->map, i - 1 * sizeof(char), i * sizeof(char*));
		params->map[i-1] = ft_strdup(*line);
		get_next_line(fd, line);
	}
	params->map = ft_realloc(params->map, i * sizeof(char), i + 1 * sizeof(char*));
	params->map[i] = NULL;
}

t_params	init_params(void)
{
	t_params	params;

	params.res_x = -1;
	params.res_y = -1;
	params.no_path = NULL;
	params.so_path = NULL;
	params.ea_path = NULL;
	params.we_path = NULL;
	params.sp_path = NULL;
	params.floor_col = 0x00000000;
	params.ceilg_col = 0x00000000;
	params.map = NULL;
	params.err = NULL;
	return (params);
}

t_params	parse_file(char *path)
{
	int			fd;
	char		*line;
	t_params	params;

	line = NULL;
	params = init_params();
	fd = open(path, O_RDONLY);
	if(read(fd, line, 0) != 0)
		params.err = ft_strdup("File invalid or not found\n");
	else
		while (get_next_line(fd, &line) > 0)
		{
			if(line[0] == 'R')
				get_res(&params, line);
			else if(line[0] == 'F')
				params.floor_col = get_fccol(line);
			else if(line[0] == 'C')
				params.ceilg_col = get_fccol(line);
			else if(line[0] == 'N' && line[1] == 'O')
				params.no_path = get_path(line + 2);
			else if(line[0] == 'S' && line[1] == 'O')
				params.so_path = get_path(line + 2);
			else if(line[0] == 'W' && line[1] == 'E')
				params.we_path = get_path(line + 2);
			else if(line[0] == 'E' && line[1] == 'A')
				params.ea_path = get_path(line + 2);
			else if(line[0] == 'S')
				params.sp_path = get_path(line + 1);
			else if(ft_split(line, ' ')[0][0] == '1')
				deal_map(&params, &line, fd);
			// else if (ft_strlen(line) == 0)
			// 	ft_printf("coucou\n");
			else
			{
				params.err = ft_strdup("Unexpected parameter.\n");
				break ;
			}
		}
	return params;
}
