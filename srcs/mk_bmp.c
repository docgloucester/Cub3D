/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:06:17 by rgilles           #+#    #+#             */
/*   Updated: 2020/11/07 16:06:18 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	file_header(int nblines, int lineweight, int fd)
{
	unsigned char	header[14];
	int				size;

	ft_bzero(&header, 14);
	size = 14 + 40 + lineweight * nblines;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(14 + 40);
	return (write(fd, header, 14));
}

int	info_header(int height, int width, int fd)
{
	unsigned char	header[40];

	ft_bzero(&header, 40);
	header[0] = (unsigned char)(40);
	header[4] = (unsigned char)(width);
	header[5] = (unsigned char)(width >> 8);
	header[6] = (unsigned char)(width >> 16);
	header[7] = (unsigned char)(width >> 24);
	header[8] = (unsigned char)(height);
	header[9] = (unsigned char)(height >> 8);
	header[10] = (unsigned char)(height >> 16);
	header[11] = (unsigned char)(height >> 24);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(4 * 8);
	return (write(fd, header, 40));
}

int	mk_bmp(char *image, int height, int width)
{
	int	fd;
	int	i;
	int ret;

	fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	ret = file_header(height, width * 4, fd);
	if (ret == -1)
		return (-1);
	ret = info_header(height, width, fd);
	if (ret == -1)
		return (-1);
	i = height;
	while (i-- >= 0)
	{
		ret = write(fd, image + (i * width * 4), width * 4);
		if (ret == -1)
			return (ret);
	}
	close(fd);
	return (0);
}
