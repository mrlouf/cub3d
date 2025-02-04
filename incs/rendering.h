/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:39:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 17:29:20 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

//DRAWING functions
void	cub_loop(void *param);
int		cub_init_pixels(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_draw_sprite_column(t_cub *cub, int x, int sprite_size, int tex_x);
void	cub_draw_player(t_cub *cub);
void	cub_draw_background(t_cub *cub);
void	cub_draw_minipx(t_cub *cub, int j, int i, int colour);
void	cub_update_pixels(t_cub *cub, t_ray *ray, int x);
int		cub_prep_wall_textures(t_cub *cub);
int		cub_prep_player_textures(t_cub *cub);
int		cub_prep_cow_textures(t_cub *cub);
void	cub_draw_npcs(t_cub *cub);
void	cub_init_sprites(t_cub *cub, t_list **sprites);
int		cub_is_sprite(char c);

//BUFFER CLEARING functions
void	cub_clear_image(mlx_image_t *img);
void	cub_clear_image_fast(mlx_image_t *img);

#endif