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

void		free_split(char **split)
{
	int	i;

	i = 0;
	while(split[i])
		free(split[i++]);
	free(split);
}

void		get_res(t_params *params, char *line)
{
	char	**line_content;

	line_content = ft_split(line , ' ');
	if (line_content && line_content[0] && line_content[1] && !line_content[2])
	{
		params->res_x = ft_atoi(line_content[0]);
		params->res_y = ft_atoi(line_content[1]);
	}
	else
		params->err = "Number of variables on screen resolution line must be 2 !\n";
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
			toret = 0xFF << 24 | ft_atoi(lico[0]) << 16;
			toret = toret | ft_atoi(lico[1]) << 8;
			toret = toret | ft_atoi(lico[2]) << 0;
		}
		else
			params->err = "Colour selection line must be 1 comma-separated array of 3 values!\n";
	}
	else
		params->err = "Colour selection line must be 1 comma-separated array of 3 values!\n";
	if (lico)
		free_split(lico);
	return (toret);
}

char		*get_path(t_params *params, char *line)
{
	char	**line_content;

	line_content = ft_split(line , ' ');
	if (line_content && line_content[0] && !line_content[1])
		return (line_content[0]);
	else
	{
		params->err = "Number of variables on path definition line must be 2 !\n";
		return (NULL);
	}
	if (line_content)
		free_split(line_content);
}

void		deal_map(t_params *params, char	**line, int fd)
{
	int		i;
	char	**splt;

	i = 1;
	params->map = (char**)malloc(i * sizeof(char*));
	params->map[0] = ft_strdup(*line);
	free(*line);
	get_next_line(fd, line);
	splt = ft_split(*line, ' ');
	while (splt[0] != NULL && splt[0][0] == '1')
	{
		i++;
		params->map = ft_realloc(params->map, (i - 1) * sizeof(char*), i * sizeof(char*));
		params->map[i-1] = ft_strdup(*line);
		free_split(splt);
		free(*line);
		get_next_line(fd, line);
		splt = ft_split(*line, ' ');
	}
	free_split(splt);
	params->map = ft_realloc(params->map, i * sizeof(char*), (i + 1) * sizeof(char*));
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
	char		**splt;
	t_params	params;

	line = NULL;
	params = init_params();
	fd = open(path, O_RDONLY);
	if(read(fd, line, 0) != 0)
		params.err = ft_strdup("File invalid or not found !\n");
	else
		while (get_next_line(fd, &line) > 0)
		{
			splt = ft_split(line, ' ');
			if(line[0] == 'R')
			{
				get_res(&params, line + 1);
			}
			else if(line[0] == 'F')
			{
				params.floor_col = get_fccol(&params,line + 1);
			}
			else if(line[0] == 'C')
			{
				params.ceilg_col = get_fccol(&params,line + 1);
			}
			else if(line[0] == 'N' && line[1] == 'O')
			{
				params.no_path = get_path(&params, line + 2);
			}
			else if(line[0] == 'S' && line[1] == 'O')
			{
				params.so_path = get_path(&params, line + 2);
			}
			else if(line[0] == 'W' && line[1] == 'E')
			{
				params.we_path = get_path(&params, line + 2);
			}
			else if(line[0] == 'E' && line[1] == 'A')
			{
				params.ea_path = get_path(&params, line + 2);
			}
			else if(line[0] == 'S')
			{
				params.sp_path = get_path(&params, line + 1);
			}
			else if(splt[0] != NULL && splt[0][0] == '1')
			{
				deal_map(&params, &line, fd);
			}
			else if (ft_strlen(line) == 0)
				;
			else
			{
				params.err = ft_strdup("Unexpected parameter !\n");
				free_split(splt);
				free(line);
				break ;
			}
			free(line);
			free_split(splt);
		}
	return params;
}
