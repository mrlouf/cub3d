/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:05:41 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 11:49:30 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "cub3d.h"

void	cub_movements(t_cub *cub);
void	cub_move_right(t_cub *cub, double speed);
void	cub_move_left(t_cub *cub, double speed);
void	cub_move_forward(t_cub *cub, double speed);
void	cub_move_backward(t_cub *cub);
void	cub_rotate_right(t_cub *cub);
void	cub_rotate_left(t_cub *cub);

//PETTING functions
void	cub_pet(t_cub *cub);
void	cub_update_frame(t_cub *cub, int *frame, int *is_petting,
			double *last_time);
void	cub_start_shooting(int *is_petting, int *frame, double *last_time);
int		cub_should_update_frame(double last_time, double frame_duration);
void	cub_reset_animation(t_player_img *player_img);
void	cub_set_frame(t_player_img *player_img, int frame_num);
void	cub_disable_all_frames(t_player_img *player_img);

#endif