/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 15:13:57 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

void	cub_update_cow_animation(t_cub *cub, double current_time)
{
	if (current_time - cub->cow_txt->last_frame_time
		>= cub->cow_txt->frame_duration)
	{
		cub->cow_txt->current_frame = (cub->cow_txt->current_frame + 1) % 6;
		cub->cow_txt->last_frame_time = current_time;
	}
}

static void	cub_get_cow_frame(t_cub *cub)
{
	if (cub->cow_txt->current_frame == 0)
		cub->cow_txt->c_t = cub->cow_txt->cow_1;
	else if (cub->cow_txt->current_frame == 1)
		cub->cow_txt->c_t = cub->cow_txt->cow_2;
	else if (cub->cow_txt->current_frame == 2)
		cub->cow_txt->c_t = cub->cow_txt->cow_3;
	else if (cub->cow_txt->current_frame == 3)
		cub->cow_txt->c_t = cub->cow_txt->cow_4;
	else if (cub->cow_txt->current_frame == 5)
		cub->cow_txt->c_t = cub->cow_txt->cow_5;
	else
		cub->cow_txt->c_t = cub->cow_txt->cow_6;
}

static void	cub_put_cow_pixel(t_cub *cub, uint8_t *pixel, int coords[2],
			int layer)
{
	uint32_t	color;

	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	if (layer == 1)
		mlx_put_pixel(cub->obj_img_b, coords[0], coords[1], color);
	else
		mlx_put_pixel(cub->obj_img_f, coords[0], coords[1], color);
}

static void	cub_process_cow_pixel(t_cub *cub, t_sprite *s, int coords[2],
				int l)
{
	int		tex_y;
	uint8_t	*pixel;

	tex_y = (coords[1] - cub->cow_txt->draw_start_y)
		* cub->cow_txt->c_t->height / s->sprite_size;
	pixel = &cub->cow_txt->c_t->pixels[(tex_y
			* cub->cow_txt->c_t->width + s->tex_x) * 4];
	if (pixel[3] > 0)
		cub_put_cow_pixel(cub, pixel, coords, l);
}

void	cub_draw_cow(t_cub *cub, int x, t_sprite *sprite, int layer)
{
	int	y;
	int	coords[2];

	cub_get_cow_frame(cub);
	cub->cow_txt->draw_start_y = (WINDOW_HEIGHT - sprite->sprite_size) / 2;
	cub->cow_txt->draw_end_y = (WINDOW_HEIGHT + sprite->sprite_size) / 2;
	y = cub->cow_txt->draw_start_y - 1;
	while (++y < cub->cow_txt->draw_end_y)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
		{
			coords[0] = x;
			coords[1] = y;
			cub_process_cow_pixel(cub, sprite, coords, layer);
		}
	}
}
