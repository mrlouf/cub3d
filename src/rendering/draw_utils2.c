/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:00:51 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 10:18:36 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"

//! More efficient clear function using memset if performance is an issue
void	cub_clear_image_fast(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(uint32_t));
}

void	cub_clear_image(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			mlx_put_pixel(img, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}
