/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:37:37 by rgilles           #+#    #+#             */
/*   Updated: 2020/07/24 14:37:38 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>

typedef	struct	s_params
{
	int		res_x;
	int		res_y;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	char	*sp_path;
	int		floor_col;
	int		ceil_col;
	int		err;
}				t_params;

#endif
