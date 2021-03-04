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

int			free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (1);
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

void		is_map(t_params *params, char **line, int fd)
{
	char	**splt;

	splt = ft_split(*line, ' ');
	if (splt[0] != NULL && ft_isdigit(splt[0][0]))
		dup_map(params, line, fd);
	else
		params->err = ft_strdup("Unexpected parameter !\n");
	free_split(splt);
}

void		push_params(t_params *params, char **line, int i, int fd)
{
	if ((*line)[i] == 'R' && params->res_y == -1)
		get_res(params, *line + i + 1);
	else if ((*line)[i] == 'F' && params->floor_col == 0)
		params->floor_col = get_col(params, *line + i + 1);
	else if ((*line)[i] == 'C' && params->ceilg_col == 0)
		params->ceilg_col = get_col(params, *line + i + 1);
	else if ((*line)[i] == 'N' && (*line)[i + 1] == 'O' && params->no_path == 0)
		params->no_path = get_path(params, *line + i + 2);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == 'O' && params->so_path == 0)
		params->so_path = get_path(params, *line + i + 2);
	else if ((*line)[i] == 'W' && (*line)[i + 1] == 'E' && params->we_path == 0)
		params->we_path = get_path(params, *line + i + 2);
	else if ((*line)[i] == 'E' && (*line)[i + 1] == 'A' && params->ea_path == 0)
		params->ea_path = get_path(params, *line + i + 2);
	else if ((*line)[i] == 'S' && params->sp_path == 0)
		params->sp_path = get_path(params, *line + i + 1);
	else if (ft_strlen(*line + i) == 0)
		;
	else
		is_map(params, line, fd);
}

t_params	parse_file(char *path)
{
	int			fd;
	char		*line;
	t_params	params;
	int			i;

	line = NULL;
	params = init_params();
	fd = open(path, O_RDONLY);
	if (read(fd, line, 0) != 0)
		params.err = ft_strdup("Specified file invalid or not found !\n");
	else if (
		ft_strnstr(path, ".cub", ft_strlen(path)) != path + ft_strlen(path) - 4)
		params.err = ft_strdup("Argument isn't a .cub file !\n");
	else
		while (get_next_line(fd, &line) > 0)
		{
			i = 0;
			while (line[i] == ' ')
				i++;
			push_params(&params, &line, i, fd);
			free(line);
		}
	free(line);
	return (params);
}
