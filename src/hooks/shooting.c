/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:40:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 09:08:47 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

void	cub_bang(t_cub *cub)
{
	static double	last_time = 0;
	static int		frame = 0;
	static int		is_shooting = 0;
	double			current_time;
	const double	frame_duration = 0.05;

	if (mlx_is_mouse_down(cub->mlx, MLX_MOUSE_BUTTON_LEFT) && !is_shooting)
	{
		is_shooting = 1;
		frame = 0;
		last_time = mlx_get_time();
	}
	if (is_shooting)
	{
		current_time = mlx_get_time();
		if (current_time - last_time >= frame_duration)
		{
			cub->player_img->p_1->enabled = false;
			cub->player_img->p_2->enabled = false;
			cub->player_img->p_3->enabled = false;
			cub->player_img->p_4->enabled = false;
			switch (frame)
			{
				case 0:
					cub->player_img->p_1->enabled = true;
					break;
				case 1:
					cub->player_img->p_2->enabled = true;
					break;
				case 2:
					cub->player_img->p_3->enabled = true;
					break;
				case 3:
					cub->player_img->p_4->enabled = true;
					break;
			}
			frame++;
			last_time = current_time;
			if (frame >= 4)
			{
				frame = 0;
				is_shooting = 0;
				cub->player_img->p_1->enabled = true;
				cub->player_img->p_2->enabled = false;
				cub->player_img->p_3->enabled = false;
				cub->player_img->p_4->enabled = false;
			}
		}
	}
}

/*void	cub_bang(t_cub *cub)
{
	static int	frame = 0;
	static int	is_shooting = 0;

	if (mlx_is_mouse_down(cub->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		is_shooting = 1;
	}
	if (is_shooting)
	{
		frame++;
		if (frame <= 5)
		{
			cub->player_img->p_1->enabled = true;
			cub->player_img->p_2->enabled = false;
			cub->player_img->p_3->enabled = false;
			cub->player_img->p_4->enabled = false;
		}
		else if (frame <= 10)
		{
			cub->player_img->p_1->enabled = false;
			cub->player_img->p_2->enabled = true;
			cub->player_img->p_3->enabled = false;
			cub->player_img->p_4->enabled = false;
		}
		else if (frame <= 15)
		{
			cub->player_img->p_1->enabled = false;
			cub->player_img->p_2->enabled = false;
			cub->player_img->p_3->enabled = true;
			cub->player_img->p_4->enabled = false;
		}
		else if (frame <= 20)
		{
			cub->player_img->p_1->enabled = false;
			cub->player_img->p_2->enabled = false;
			cub->player_img->p_3->enabled = false;
			cub->player_img->p_4->enabled = true;
		}
		if (frame >= 20)
		{
			frame = 0;
			is_shooting = 0;
		}
	}
	else
	{
		cub->player_img->p_1->enabled = false;
		cub->player_img->p_2->enabled = false;
		cub->player_img->p_3->enabled = false;
		cub->player_img->p_4->enabled = true;
	}
}*/
