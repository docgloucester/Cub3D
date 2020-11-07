/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:29:24 by rgilles           #+#    #+#             */
/*   Updated: 2020/10/28 14:29:26 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void createBitmapFileHeader (int nblines, int lineweight, int fd)
{
    int fileSize = 14 + 40 + lineweight * nblines;

    static unsigned char fileHeader[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(14 + 40);
    write(fd, fileHeader, 14);
}

void createBitmapInfoHeader (int height, int width, int fd)
{
    static unsigned char infoHeader[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    infoHeader[ 0] = (unsigned char)(40);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(4*8);
    write(fd, infoHeader, 40);
}

void create_bmp (char* image, int height, int width)
{
    int				fd;
    int				i;

    fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    createBitmapFileHeader(height, width * 4, fd);
    createBitmapInfoHeader(height, width, fd);
    i = height;
    while (i-- >= 0)
        write(fd, image + (i * width * 4), width * 4);
    close(fd);
}
