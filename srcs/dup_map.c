/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:08:39 by rgilles           #+#    #+#             */
/*   Updated: 2020/09/01 17:08:40 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		check_line(t_params *params, char **line, int fd)
{
	int			len;
	static int	count;

	if (count++)
	{
		free(*line);
		get_next_line(fd, line);
	}
	len = ft_strlen(*line);
	while (--len >= 0)
		if (!(params->err) && (!(ft_strchr(" 012NSEW", (*line)[len]))))
		{
			params->err = ft_strdup("Map invalid !\n");
			return (1);
		}
	return (0);
}

void	check_eof(t_params *params, char **line, int fd)
{
	free(*line);
	while (get_next_line(fd, line))
	{
		if (!(params->err) && *line[0] != '\0')
			params->err = ft_strdup("File doesn't end with detected map !\n");
		free(*line);
	}
	trim_map_y(params);
	trim_map_x(params);
}

void	dup_map(t_params *params, char **line, int fd)
{
	int		i;
	char	**splt;

	if (check_line(params, line, fd))
		return ;
	params->map = (char**)malloc(sizeof(char*));
	params->map[0] = ft_strdup(*line);
	check_line(params, line, fd);
	splt = ft_split(*line, ' ');
	i = 1;
	while (splt[0] != NULL && ft_isdigit(splt[0][0]) && (i++))
	{
		params->map = ft_realloc(params->map, (i - 1) * sizeof(char*),
			i * sizeof(char*));
		params->map[i - 1] = ft_strdup(*line);
		free_split(splt);
		check_line(params, line, fd);
		splt = ft_split(*line, ' ');
	}
	free_split(splt);
	params->map = ft_realloc(params->map, i * sizeof(char*),
		(i + 1) * sizeof(char*));
	params->map[i] = NULL;
	check_eof(params, line, fd);
}
