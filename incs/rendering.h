/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:39:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 16:29:04 by nponchon         ###   ########.fr       */
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
int		cub_prep_wall_textures(t_cub *cub);
void	set_texture_and_wall(t_texture_data *data, t_cub *cub, t_ray *ray);
void	calculate_texture_position(t_texture_data *data, t_ray *ray);
void	cub_calculate_door_distance(t_ray *ray);
void	cub_calculate_door_height(t_ray *ray);
void	cub_set_texture_door(t_texture_data *data, t_cub *cub, t_ray *ray);
void	cub_calculate_door_texture(t_texture_data *data, t_ray *ray);
void	cub_draw_doors(t_cub *cub, t_ray *ray, int x);

#endif