/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pet_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:40:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 11:36:07 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

void	cub_disable_all_frames(t_player_img *player_img)
{
	player_img->p_1->enabled = false;
	player_img->p_2->enabled = false;
	player_img->p_3->enabled = false;
	player_img->p_4->enabled = false;
}

void	cub_set_frame(t_player_img *player_img, int frame_num)
{
	cub_disable_all_frames(player_img);
	if (frame_num == 0)
		player_img->p_1->enabled = true;
	if (frame_num == 1)
		player_img->p_2->enabled = true;
	if (frame_num == 2)
		player_img->p_3->enabled = true;
	if (frame_num == 3)
		player_img->p_4->enabled = true;
}
