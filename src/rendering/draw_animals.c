/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_animals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/05 12:21:27 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

void	cub_draw_horse(t_cub *cub, int x, t_sprite *sprite)
{
	int		draw_start_y;
	int		draw_end_y;
	int		y;
	int		tex_y;
	uint8_t	*pixel;

	draw_start_y = (WINDOW_HEIGHT - sprite->sprite_size) / 2;
	draw_end_y = (WINDOW_HEIGHT + sprite->sprite_size) / 2;
	y = draw_start_y;
	while (y < draw_end_y)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
		{
			tex_y = (y - draw_start_y) * cub->horse_txt->height
				/ sprite->sprite_size;
			pixel = &cub->horse_txt->pixels[(tex_y * cub->horse_txt->width
					+ sprite->tex_x) * 4];
			if (pixel[3] > 0)
				mlx_put_pixel(cub->obj_img, x, y,
					(pixel[0] << 24) | (pixel[1] << 16)
					| (pixel[2] << 8) | pixel[3]);
		}
		y++;
	}
}

void	cub_draw_cow(t_cub *cub, int x, t_sprite *sprite)
{
	int		draw_start_y;
	int		draw_end_y;
	int		y;
	int		tex_y;
	uint8_t	*pixel;

	draw_start_y = (WINDOW_HEIGHT - sprite->sprite_size) / 2;
	draw_end_y = (WINDOW_HEIGHT + sprite->sprite_size) / 2;
	y = draw_start_y;
	while (y < draw_end_y)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
		{
			tex_y = (y - draw_start_y) * cub->cow_txt->height
				/ sprite->sprite_size;
			pixel = &cub->cow_txt->pixels[(tex_y * cub->cow_txt->width
					+ sprite->tex_x) * 4];
			if (pixel[3] > 0)
				mlx_put_pixel(cub->obj_img, x, y,
					(pixel[0] << 24) | (pixel[1] << 16)
					| (pixel[2] << 8) | pixel[3]);
		}
		y++;
	}
}
