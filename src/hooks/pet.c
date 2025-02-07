/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pet.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:40:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 15:12:56 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

void	cub_reset_animation(t_player_img *player_img)
{
	cub_disable_all_frames(player_img);
	player_img->p_1->enabled = true;
}

int	cub_should_update_frame(double last_time, double frame_duration)
{
	double	current_time;

	current_time = mlx_get_time();
	return (current_time - last_time >= frame_duration);
}

void	cub_start_shooting(int *is_petting, int *frame, double *last_time)
{
	*is_petting = 1;
	*frame = 0;
	*last_time = mlx_get_time();
}

void	cub_update_frame(t_cub *cub, int *frame, int *is_petting,
	double *last_time)
{
	cub_set_frame(cub->player_img, *frame);
	(*frame)++;
	*last_time = mlx_get_time();
	if (*frame >= 4)
	{
		*frame = 0;
		*is_petting = 0;
		cub_reset_animation(cub->player_img);
	}
}

void	cub_pet(t_cub *cub)
{
	static double	last_time = 0;
	static int		frame = 0;
	static int		is_petting = 0;
	const double	frame_duration = 0.05;

	if ((mlx_is_mouse_down(cub->mlx, MLX_MOUSE_BUTTON_LEFT)
			|| mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT_CONTROL)) && !is_petting)
		cub_start_shooting(&is_petting, &frame, &last_time);
	if (!is_petting)
		return ;
	if (!cub_should_update_frame(last_time, frame_duration))
		return ;
	cub_update_frame(cub, &frame, &is_petting, &last_time);
}
