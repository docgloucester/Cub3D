/* ************************************************************************** */
/*																																						*/
/*																												:::			::::::::	 */
/*	 check_error.c																			:+:			:+:		:+:	 */
/*																										+:+ +:+				 +:+		 */
/*	 By: rgilles <rgilles@student.42.fr>						+#+	+:+			 +#+				*/
/*																								+#+#+#+#+#+	 +#+					 */
/*	 Created: 2021/02/19 20:33:52 by rgilles					 #+#		#+#						 */
/*	 Updated: 2021/02/19 20:34:04 by rgilles					###	 ########.fr			 */
/*																																						*/
/* ************************************************************************** */

#include <cub3d.h>

void	check_error(t_vars *mywin)
{
	int	max_x;
	int	max_y;

	if (mywin->params.err)
		return ;
	if (!(mywin->params.res_x && mywin->params.res_y))
		mywin->params.err = "Resolution unset.\n";
	if (!(mywin->params.so_path && mywin->params.no_path && mywin->params.ea_path
		&& mywin->params.we_path && mywin->params.sp_path))
		mywin->params.err = "Texture paths unset.\n";
	if (!(mywin->params.floor_col && mywin->params.ceilg_col))
		mywin->params.err = "Background colours unset.\n";
	if (!mywin->params.map)
		mywin->params.err = "No map\n";
	mlx_get_screen_size(mywin->mlx, &max_x, &max_y);
	if (mywin->params.res_x > max_x || mywin->params.res_y > max_y)
	{
		ft_printf("Warning : the current screen resolution is inferior to the one specified.");
		ft_printf("Falling back to current resolution\n");
		mywin->params.res_x = max_x;
		mywin->params.res_y = max_y;
	}
}

void	check_map_closed(t_vars*mywin)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
	}
}

void floodFillScanline(Uint32* screenBuffer, int w, int h, int x, int y, int newColor, int oldColor)
{
	int x1;

	//draw current scanline from start position to the right
	x1 = x;
	while(map[y][x1] != '1' && map[y][x1] != '2')
		x1++;
	//draw current scanline from start position to the left
	x1 = x - 1;
	while(map[y][x1] != '1' && map[y][x1] != '2')
		x1--;
	//test for new scanlines above
	x1 = x;
	while(x1 < w && screenBuffer[y * w + x1] == newColor)
	{
		if(y > 0 && screenBuffer[(y - 1) * w + x1] == oldColor)
		{
			floodFillScanline(screenBuffer, w, h, x1, y - 1, newColor, oldColor);
		}
		x1++;
	}
	x1 = x - 1;
	while(x1 >= 0 && screenBuffer[y * w + x1] == newColor)
	{
		if(y > 0 && screenBuffer[(y - 1) * w + x1] == oldColor)
		{
			floodFillScanline(screenBuffer, w, h, x1, y - 1, newColor, oldColor);
		}
		x1--;
	}
	//test for new scanlines below
	x1 = x;
	while(x1 < w && screenBuffer[y * w + x1] == newColor)
	{
		if(y < h - 1 && screenBuffer[(y + 1) * w + x1] == oldColor)
		{
			floodFillScanline(screenBuffer, w, h, x1, y + 1, newColor, oldColor);
		}
		x1++;
	}
	x1 = x - 1;
	while(x1 >= 0 && screenBuffer[y * w + x1] == newColor)
	{
		if(y < h - 1 && screenBuffer[(y + 1) * w + x1] == oldColor)
		{
			floodFillScanline(screenBuffer, w, h, x1, y + 1, newColor, oldColor);
		}
		x1--;
	}
}