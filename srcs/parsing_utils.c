/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:17:51 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/04 13:18:06 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_res(t_params *params, char *line)
{
	char	**line_content;

	line_content = ft_split(line, ' ');
	if (line_content && line_content[0] && line_content[1] && !line_content[2])
	{
		params->res_x = ft_atoi(line_content[0]);
		params->res_y = ft_atoi(line_content[1]);
		if ((params->res_x < 4 || params->res_y < 4) && !(params->err))
			params->err = ft_strdup("Invalid resolution !\n");
	}
	else if (!(params->err))
		params->err = ft_strdup("Number of variables on R line must be 2 !\n");
	if (line_content)
		free_split(line_content);
}

int		push_col(t_params *params, char **lico)
{
	int toret;

	if ((ft_atoi(lico[0]) < 0 || ft_atoi(lico[1]) < 0 || ft_atoi(lico[2]) < 0
		|| ft_atoi(lico[0]) > 255 || ft_atoi(lico[1]) > 255
		|| ft_atoi(lico[2]) > 255) && !(params->err))
	{
		params->err = ft_strdup("Invalid colour!\n");
		free_split(lico);
		return (0);
	}
	toret = 0x00 << 24 | ft_atoi(lico[0]) << 16;
	toret = toret | ft_atoi(lico[1]) << 8;
	toret = toret | ft_atoi(lico[2]) << 0;
	return (toret);
}

int		get_col(t_params *params, char *line)
{
	int		toret;
	char	**lico;
	char	*trimmed_line;

	lico = ft_split(line, ' ');
	toret = 0;
	if (lico && lico[0] && !lico[1])
	{
		trimmed_line = ft_strdup(lico[0]);
		free_split(lico);
		lico = ft_split(trimmed_line, ',');
		free(trimmed_line);
		if (lico && lico[0] && lico[1] && lico[2] && !lico[3])
		{
			if ((toret = push_col(params, lico)) == 0)
				return (0);
		}
		else if (!(params->err))
			params->err = ft_strdup("Colour array doesn't have 3 values!\n");
	}
	else if (!(params->err))
		params->err = ft_strdup("Colour line isn't a comma-separated array!\n");
	if (lico)
		free_split(lico);
	return (toret);
}

char	*get_path(t_params *params, char *line)
{
	char	**line_content;
	char	*path;
	int		fd;

	line_content = ft_split(line, ' ');
	if (line_content && line_content[0] && !line_content[1])
	{
		path = ft_strdup(line_content[0]);
		free_split(line_content);
		fd = open(path, O_RDONLY);
		if (read(fd, line, 0) != 0 && !(params->err))
			params->err = ft_strdup("Texture file invalid or not found !\n");
		return (path);
	}
	else
	{
		if (line_content)
			free_split(line_content);
		if (!(params->err))
			params->err = ft_strdup("More than 1 parameter on path line !\n");
		return (NULL);
	}
}
