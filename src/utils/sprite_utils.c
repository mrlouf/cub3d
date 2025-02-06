/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 12:50:55 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"
#include "../../incs/rendering.h"

void	cub_select_sprite(t_cub *cub, int x, t_sprite *sprite, int layer)
{
	if (sprite->type == COW)
		cub_draw_cow(cub, x, sprite, layer);
	else if (sprite->type == HORSE)
		cub_draw_horse(cub, x, sprite, layer);
	else if (sprite->type == NPC1)
		cub_draw_npc1(cub, x, sprite, layer);
}

void	cub_get_sprite_width(t_cub *cub, t_sprite *sprite)
{
	if (sprite->type == COW)
		sprite->width = cub->cow_txt->width;
	else if (sprite->type == HORSE)
		sprite->width = cub->horse_txt->width;
	else if (sprite->type == NPC1)
		sprite->width = cub->npc_1_txt->width;
}
