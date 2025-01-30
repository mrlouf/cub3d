/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:39:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 12:48:31 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

void	cub_loop(void *param);
int		cub_init_pixels(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_draw_background(t_cub *cub);
void	cub_draw_minipx(t_cub *cub, int j, int i, int colour);
void	cub_update_pixels(t_cub *cub, t_ray *ray, int x);

#endif