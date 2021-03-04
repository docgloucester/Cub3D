/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:37 by rgilles           #+#    #+#             */
/*   Updated: 2021/03/04 11:11:52 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	trim_map_y2(t_params *params, int hi, int lo, int *i)
{
	if (hi > 0 && lo > hi)
	{
		*i = 0;
		while (*i < hi)
			free(params->map[(*i)++]);
		while (*i <= lo)
		{
			params->map[*i - hi] = params->map[*i];
			(*i)++;
		}
		while (*i <= lo + hi)
		{
			params->map[*i - hi] = NULL;
			(*i)++;
		}
	}
	else
		*i = lo + hi + 1;
}

void	trim_map_y(t_params *params)
{
	int		highest;
	int		lowest;
	int		i;

	highest = 0;
	while (params->map[highest] && !ft_strchr(params->map[highest], '1'))
		highest++;
	lowest = 0;
	while (params->map[lowest])
		lowest++;
	lowest--;
	while (lowest >= 0 && !ft_strchr(params->map[lowest], '1'))
		lowest--;
	trim_map_y2(params, highest, lowest, &i);
	while (params->map[i - highest])
	{
		free(params->map[i - highest]);
		params->map[i - highest] = NULL;
		i++;
	}
	params->map_y = lowest - highest + 1;
}

int		trim_map_x2(t_params *params, int *i, int *j)
{
	int	rightest;

	*i = 0;
	rightest = 0;
	while (params->map[*i])
	{
		*j = ft_strlen(params->map[*i]) - 1;
		while (*j >= 0 && params->map[*i][*j] != '1')
			(*j)--;
		if (*j > rightest)
			rightest = *j;
		(*i)++;
	}
	*i = 0;
	return (rightest);
}

void	trim_map_x(t_params *params)
{
	int		i;
	int		j;
	int		leftest;
	int		rightest;
	char	*defausse;

	i = 0;
	leftest = 1000;
	while (params->map[i])
	{
		j = 0;
		while (params->map[i][j] && params->map[i][j] != '1')
			j++;
		if (j < leftest)
			leftest = j;
		i++;
	}
	rightest = trim_map_x2(params, &i, &j);
	while (params->map[i])
	{
		defausse = params->map[i];
		params->map[i++] = ft_substr(defausse, leftest, rightest - leftest + 1);
		free(defausse);
	}
	params->map_x = rightest - leftest + 1;
}
