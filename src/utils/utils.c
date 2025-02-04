/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 10:20:36 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

void	cub_draw_minipx(t_cub *cub, int j, int i, int colour);

/*
	Good old line drawing algo from FDF. It takes a start point and an
	end point as parameters and draws a line between the two points, with the
	colour as the last parameter.
*/
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
			&& (uint32_t)delta.y * cub->minimap_px < WINDOW_HEIGHT)
		{
			cub_draw_minipx(cub, delta.y * cub->minimap_px, \
		delta.x * cub->minimap_px, colour);
		}
		delta.x += delta.dx;
		delta.y += delta.dy;
	}
}
