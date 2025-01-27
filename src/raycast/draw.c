/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/27 20:17:39 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/raycast.h"

/*
	Draws the floor by painting the bottom half of the screen
	in a certain colour.
*/
void	cub_draw_floor(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = WINDOW_HEIGHT / 2;
		while (j < WINDOW_HEIGHT)
		{
			mlx_put_pixel(cub->img, i, j, 0x8B4513FF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

void	cub_draw(t_cub *cub)
{
	cub_draw_floor(cub);
}
