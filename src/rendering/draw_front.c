/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_front.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 15:11:33 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

static void	draw_sprite_line(t_cub *cub, t_sprite *sprite, int x)
{
	if (x >= 0 && x < WINDOW_WIDTH)
	{
		if (sprite->transform_y < cub->zbuffer[x].wall_dist
			&& sprite->transform_y <= cub->zbuffer[x].door_dist)
		{
			sprite->tex_x = (x - sprite->draw_start_x)
				* sprite->width / sprite->sprite_size;
			cub_select_sprite(cub, x, sprite, 2);
		}
	}
}

static void	process_sprite(t_cub *cub, t_sprite *sprite)
{
	int	x;

	cub_calculate_sprite(cub, sprite);
	x = sprite->draw_start_x;
	while (x < sprite->draw_end_x)
	{
		draw_sprite_line(cub, sprite, x);
		x++;
	}
}

static void	update_sprites(t_cub *cub, t_list *current)
{
	t_sprite	*sprite;

	while (current)
	{
		sprite = current->content;
		cub_update_sprite(cub, sprite);
		current = current->next;
	}
}

void	cub_draw_obj_in_front_doors(t_cub *cub)
{
	t_list		*current;
	t_sprite	*sprite;

	current = cub->sprites;
	update_sprites(cub, current);
	cub_sort_sprites(&cub->sprites);
	current = cub->sprites;
	while (current)
	{
		sprite = current->content;
		process_sprite(cub, sprite);
		current = current->next;
	}
}
