/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:05:41 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 12:49:16 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "cub3d.h"

void	cub_move_right(t_cub *cub, double speed);
void	cub_move_left(t_cub *cub, double speed);
void	cub_move_forward(t_cub *cub, double speed);
void	cub_move_backward(t_cub *cub);
void	cub_rotate_right(t_cub *cub);
void	cub_rotate_left(t_cub *cub);

#endif