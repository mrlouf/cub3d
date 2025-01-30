/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:00:51 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/29 14:04:58 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"

/*
	Allocates an **int matrix 'pixels', that acts as a canvas:
	each int represents a pixel in the window to be painted/drawn
	as needed for the program. Freed after the rendition,
	and allocated again for every loop of the mlx.
*/
int	cub_init_pixels(t_cub *cub)
{
	int	i;

	cub->px = malloc(sizeof(int *) * WINDOW_HEIGHT);
	if (!cub->px)
		return (1);
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		cub->px[i] = malloc(sizeof(int) * WINDOW_WIDTH);
		if (!cub->px[i])
			ft_free_narray((void **)cub->px, i);
	}
	return (0);
}

/*
	Draws the ray from the start point to the end point.
	Chooses colour depending on the side of the wall hit.
*/
void	cub_update_pixels(t_cub *cub, t_ray *ray, int x)
{
	int	i;
	int	colour;

	i = ray->start;
	colour = 0x660000FF;
	if (ray->side != 0)
		colour = 0x330000FF;
	while (i < ray->end)
	{
		mlx_put_pixel(cub->img, x, i, colour);
		i++;
	}
}
