/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 20:39:36 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

void	cub_dda(t_cub *cub, t_vector start, t_vector end, int colour)
{
	t_delta	delta;
	int		i;

	delta.dx = end.x - start.x;
	delta.dy = end.y - start.y;
	if (fabs(delta.dx) >= fabs(delta.dy))
		delta.step = fabs(delta.dx);
	else
		delta.step = fabs(delta.dy);
	delta.dx = delta.dx / delta.step;
	delta.dy = delta.dy / delta.step;
	delta.x = start.x;
	delta.y = start.y;
	i = 0;
	while (i++ <= delta.step)
	{
		if ((uint32_t)delta.x * cub->minimap_px < WINDOW_WIDTH
			&& (uint32_t)delta.y * cub->minimap_px < WINDOW_HEIGHT
			&& (uint32_t)delta.x * cub->minimap_px > 0
			&& (uint32_t)delta.y * cub->minimap_px > 0)
		{
			cub_draw_minipx(cub, delta.y * cub->minimap_px, \
		delta.x * cub->minimap_px, colour);
		}
		delta.x += delta.dx;
		delta.y += delta.dy;
	}
}

/*
void	cub_draw_line(t_fdf *fdf, int x, int y)
{
	if (x == fdf->map->rows && y == fdf->map->cols)
		return ;
	if (x + 1 < fdf->map->rows)
	{
		drawing_algo(fdf, fdf->map->fgrid[x][y], fdf->map->fgrid[x + 1][y]);
	}
	if (y + 1 < fdf->map->cols)
	{
		drawing_algo(fdf, fdf->map->fgrid[x][y], fdf->map->fgrid[x][y + 1]);
	}
}
*/

void	cub_clean(t_cub *cub)
{
	if (cub->player)
		free(cub->player);
	if (cub->filename)
		free(cub->filename);
	if (cub->map)
		ft_free_narray((void **)cub->map, 25);
	if (cub)
		free(cub);
}
