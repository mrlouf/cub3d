/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/05 12:27:46 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

void	cub_update_sprite(t_cub *cub, t_sprite *sprite)
{
	double	dx;
	double	dy;
	double	sprite_dir;

	dx = sprite->pos.x - cub->player->pos.x;
	dy = sprite->pos.y - cub->player->pos.y;
	sprite->distance = sqrt(dx * dx + dy * dy);
	sprite_dir = atan2(dy, dx);
	sprite->angle = sprite_dir - cub->player->angle;
	if (sprite->angle < -M_PI)
		sprite->angle += 2 * M_PI;
	if (sprite->angle > M_PI)
		sprite->angle -= 2 * M_PI;
}

void	cub_calculate_sprite(t_cub *cub, t_sprite *sprite)
{
	sprite->sprite_dx = sprite->pos.x - cub->player->pos.x;
	sprite->sprite_dy = sprite->pos.y - cub->player->pos.y;
	sprite->inv_det = 1.0 / (cub->player->plane.x * cub->player->dir.y
			- cub->player->dir.x * cub->player->plane.y);
	sprite->transform_x = sprite->inv_det * (cub->player->dir.y * \
		sprite->sprite_dx - cub->player->dir.x * sprite->sprite_dy);
	sprite->transform_y = sprite->inv_det * (-cub->player->plane.y * \
		sprite->sprite_dx + cub->player->plane.x * sprite->sprite_dy);
	if (sprite->transform_y <= 0)
		return ;
	sprite->sprite_screen_x = (int)((WINDOW_WIDTH / 2) * \
		(1 + sprite->transform_x / sprite->transform_y));
	sprite->sprite_size = abs((int)(WINDOW_HEIGHT / sprite->transform_y));
	sprite->draw_start_x = sprite->sprite_screen_x - sprite->sprite_size / 2;
	sprite->draw_end_x = sprite->sprite_screen_x + sprite->sprite_size / 2;
	cub_get_sprite_width(cub, sprite);
}

void	cub_prep_sprite(t_cub *cub, t_sprite *sprite)
{
	int	x;

	cub_calculate_sprite(cub, sprite);
	x = sprite->draw_start_x;
	while (x < sprite->draw_end_x)
	{
		if (x >= 0 && x < WINDOW_WIDTH)
		{
			if (sprite->transform_y < cub->zbuffer[x])
			{
				sprite->tex_x = (x - sprite->draw_start_x) * \
					sprite->width / sprite->sprite_size;
				cub_select_sprite(cub, x, sprite);
			}
		}
		x++;
	}
}

void	cub_draw_obj(t_cub *cub)
{
	t_list			*current;
	t_sprite		*sprite;

	cub_clear_image_fast(cub->obj_img);
	current = cub->sprites;
	while (current)
	{
		sprite = current->content;
		cub_update_sprite(cub, sprite);
		current = current->next;
	}
	cub_sort_sprites(&cub->sprites);
	current = cub->sprites;
	while (current)
	{
		sprite = current->content;
		cub_prep_sprite(cub, sprite);
		current = current->next;
	}
}
