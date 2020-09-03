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

void		trim_map_y(t_params *params)
{
int		highest;
int		lowest;
// int		i;

	highest = 0;
	while (params->map[highest] && !ft_strchr(params->map[highest], '1'))
		highest++;
	lowest = 0;
	while (params->map[lowest])
		lowest++;
	lowest--;
	while (params->map[lowest] && !ft_strchr(params->map[lowest], '1'))
		lowest--;
// 	i = highest;
// 	while (i <= lowest)
// 	{
// 		free(params->map[i - highest]);
// 		params->map[i - highest] = params->map[i];
// 		i++;
// 	}
// 	free(params->map[i - highest]);
// 	params->map[i - highest] = NULL;
// 	i++;
// 	while (params->map[i - highest])
// 	{
// 		free(params->map[i - highest]);
// 		i++;
	params->mapY = lowest - highest + 1;
}

// }

void		trim_map_x(t_params *params)
{
	int		i;
	int		j;
	int		leftest_wall_pos;
	int		rightest_wall_pos;
	char	*defausse;

	i = 0;
	leftest_wall_pos = 1000;
	while (params->map[i])
	{
		j = 0;
		while (params->map[i][j] && params->map[i][j] != '1')
			j++;
		if (j < leftest_wall_pos)
			leftest_wall_pos = j;
		i++;
	}
	i = 0;
	rightest_wall_pos = 0;
	while (params->map[i])
	{
		j = ft_strlen(params->map[i]) - 1;
		while (j >= 0 && params->map[i][j] != '1')
			j--;
		if (j > rightest_wall_pos)
			rightest_wall_pos = j;
		i++;
	}
	i = 0;
	while (params->map[i])
	{
		defausse = params->map[i];
		params->map[i++] = ft_substr(defausse, leftest_wall_pos, rightest_wall_pos - leftest_wall_pos + 1);
		free(defausse);
	}
	params->mapX = rightest_wall_pos - leftest_wall_pos + 1;
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
	while (splt[0] != NULL && ft_isdigit(splt[0][0]))
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
	trim_map_y(params);
	trim_map_x(params);
}
