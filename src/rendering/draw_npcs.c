/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 15:15:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

static void	cub_put_npc_1_pixel(t_cub *cub, uint8_t *pixel,
	int coords[2], int layer)
{
	uint32_t	color;

	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	if (layer == 1)
		mlx_put_pixel(cub->obj_img_b, coords[0], coords[1], color);
	else
		mlx_put_pixel(cub->obj_img_f, coords[0], coords[1], color);
}

static void	cub_process_npc_1_pixel(t_cub *cub,
	t_sprite *s, int coords[2], int layer)
{
	int		tex_y;
	uint8_t	*pixel;

	tex_y = (coords[1] - cub->npc_1_txt->draw_start_y)
		* cub->npc_1_txt->height / s->sprite_size;
	pixel = &cub->npc_1_txt->pixels[(tex_y
			* cub->npc_1_txt->width + s->tex_x) * 4];
	if (pixel[3] > 0)
		cub_put_npc_1_pixel(cub, pixel, coords, layer);
}

void	cub_draw_npc1(t_cub *cub, int x, t_sprite *sprite, int layer)
{
	int	y;
	int	coords[2];

	cub->npc_1_txt->draw_start_y = (WINDOW_HEIGHT - sprite->sprite_size) / 2;
	cub->npc_1_txt->draw_end_y = (WINDOW_HEIGHT + sprite->sprite_size) / 2;
	y = cub->npc_1_txt->draw_start_y - 1;
	while (++y < cub->npc_1_txt->draw_end_y)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
		{
			coords[0] = x;
			coords[1] = y;
			cub_process_npc_1_pixel(cub, sprite, coords, layer);
		}
	}
}
