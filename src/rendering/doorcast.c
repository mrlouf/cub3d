/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:41:12 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 12:14:01 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"

#include <math.h>
#include <stdlib.h>

int	cub_doorcasting(t_cub *cub, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cub_init_ray(ray, x, cub->player);
		cub_calculate_step(ray, cub->player);
		cub_calculate_wall_distance(ray, cub->map);
		cub_calculate_wall_height(ray);
		cub->zbuffer[x].wall_dist = ray->wall_d;
		if (ray->door_hit)
			cub->zbuffer[x].door_dist = ray->door_d;
		else
			cub->zbuffer[x].door_dist = INFINITY;
		if (ray->door_hit && (ray->door_d < ray->wall_d))
			cub_draw_doors(cub, ray, x);
		x++;
	}
	return (0);
}
