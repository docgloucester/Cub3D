/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:36:18 by rgilles           #+#    #+#             */
/*   Updated: 2020/07/24 12:36:20 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		i = 0;
		while (get_next_line(fd, &line))
		{
			ft_printf("Ligne n%d : %s\n", ++i, line);
			free(line);
		}
		ft_printf("Ligne n%d : %s\n", ++i, line);
		free(line);
		line = NULL;
		close(fd);
	}
	return (0);
}
