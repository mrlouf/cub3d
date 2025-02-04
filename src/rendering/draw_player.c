/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 09:00:33 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

void	cub_draw_player(t_cub *cub)
{
	mlx_image_to_window(cub->mlx, cub->player_img->p_1, \
		WINDOW_WIDTH / 2 - 390 / 2, WINDOW_HEIGHT - 390);
	mlx_image_to_window(cub->mlx, cub->player_img->p_2, \
		WINDOW_WIDTH / 2 - 390 / 2, WINDOW_HEIGHT - 390);
	mlx_image_to_window(cub->mlx, cub->player_img->p_3, \
		WINDOW_WIDTH / 2 - 390 / 2, WINDOW_HEIGHT - 390);
	mlx_image_to_window(cub->mlx, cub->player_img->p_4, \
		WINDOW_WIDTH / 2 - 390 / 2, WINDOW_HEIGHT - 390);
	cub->player_img->p_1->enabled = true;
	cub->player_img->p_2->enabled = false;
	cub->player_img->p_3->enabled = false;
	cub->player_img->p_4->enabled = false;
}
