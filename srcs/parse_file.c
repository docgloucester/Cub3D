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

int		free_split(char **split)
{
	int	i;

	i = 0;
	while(split[i])
		free(split[i++]);
	free(split);
	return (1);
}

void		get_res(t_params *params, char *line)
{
	char	**line_content;

	line_content = ft_split(line , ' ');
	if (line_content && line_content[0] && line_content[1] && !line_content[2])
	{
		params->res_x = ft_atoi(line_content[0]);
		params->res_y = ft_atoi(line_content[1]);
		if (params->res_x < 4 || params->res_y < 4)
			params->err = ft_strdup("Invalid resolution !\n");

	}
	else
		params->err = ft_strdup("Number of variables on screen resolution line must be 2 !\n");
	if (line_content)
		free_split(line_content);
}

int			get_fccol(t_params *params, char *line)
{
	int		toret;
	char	**lico;
	char	*trimmed_line;

	lico = ft_split(line , ' ');
	toret = 0;
	if (lico && lico[0] && !lico[1])
	{
		trimmed_line = ft_strdup(lico[0]);
		free_split(lico);
		lico = ft_split(trimmed_line, ',');
		free(trimmed_line);
		if (lico && lico[0] && lico[1] && lico[2] && !lico[3])
		{
			if ((ft_atoi(lico[0]) < 0 || ft_atoi(lico[1]) < 0 || ft_atoi(lico[2]) < 0
				|| ft_atoi(lico[0]) > 255 || ft_atoi(lico[1]) > 255 || ft_atoi(lico[2]) > 255
				) && (params->err = ft_strdup("Invalid colour!\n")) && (free_split(lico)))
				return (0);
			toret = 0x00 << 24 | ft_atoi(lico[0]) << 16;
			toret = toret | ft_atoi(lico[1]) << 8;
			toret = toret | ft_atoi(lico[2]) << 0;
		}
		else
			params->err = ft_strdup("Colour selection line must be 1 comma-separated array of 3 values!\n");
	}
	else
		params->err = ft_strdup("Colour selection line must be 1 comma-separated array of 3 values!\n");
	if (lico)
		free_split(lico);
	return (toret);
}

char		*get_path(t_params *params, char *line)
{
	char	**line_content;
	char	*path;
	int		fd;

	line_content = ft_split(line , ' ');
	if (line_content && line_content[0] && !line_content[1])
	{
		path = ft_strdup(line_content[0]);
		free_split(line_content);
		fd = open(path, O_RDONLY);
		if(read(fd, line, 0) != 0)
			params->err = ft_strdup("Texture file invalid or not found !\n");
		return (path);
	}
	else
	{
		if (line_content)
			free_split(line_content);
		params->err = ft_strdup("Number of variables on path definition line must be 2 !\n");
		return (NULL);
	}
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
	char		**splt;
	t_params	params;
	int			i;

	line = NULL;
//	while ()
	params = init_params();
	fd = open(path, O_RDONLY);
	if(read(fd, line, 0) != 0)
		params.err = ft_strdup("Map file invalid or not found !\n");
	else
		while (get_next_line(fd, &line) > 0)
		{
			i = 0;
			while (line[i] == ' ')
				i++;
			if(line[i] == 'R' && params.res_y == -1)
				get_res(&params, line + i + 1);
			else if(line[i] == 'F' && params.floor_col == 0)
				params.floor_col = get_fccol(&params,line + i + 1);
			else if(line[i] == 'C' && params.ceilg_col == 0)
				params.ceilg_col = get_fccol(&params,line + i + 1);
			else if(line[i] == 'N' && line[i + 1] == 'O' && params.no_path == 0)
				params.no_path = get_path(&params, line + i + 2);
			else if(line[i] == 'S' && line[i+ 1] == 'O' && params.so_path == 0)
				params.so_path = get_path(&params, line + i + 2);
			else if(line[i] == 'W' && line[i + 1] == 'E' && params.we_path == 0)
				params.we_path = get_path(&params, line + i + 2);
			else if(line[i] == 'E' && line[i + 1] == 'A' && params.ea_path == 0)
				params.ea_path = get_path(&params, line + i + 2);
			else if(line[i] == 'S' && params.sp_path == 0)
				params.sp_path = get_path(&params, line + i + 1);
			else if (ft_strlen(line + i) == 0)
				;
			else 
			{
				splt = ft_split(line, ' ');
				if(splt[0] != NULL && ft_isdigit(splt[0][0]))
				{
					deal_map(&params, &line, fd);
				}
				else
				{
					params.err = ft_strdup("Unexpected parameter !\n");
					free_split(splt);
					break ;
				}
				free_split(splt);
			}
			free(line);
		}
	free(line);
	return params;
}
