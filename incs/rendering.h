/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:39:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 15:01:41 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

//RAYCASTING functions
int		cub_raycasting(t_cub *cub, t_ray *ray);
int		cub_doorcasting(t_cub *cub, t_ray *ray);
void	cub_calculate_wall_height(t_ray *ray);
void	cub_calculate_wall_distance(t_ray *ray, int **map);
void	cub_calculate_step(t_ray *ray, t_player *player);
void	cub_init_ray(t_ray *ray, int x, t_player *player);

//DRAWING functions
void	cub_loop(void *param);
int		cub_init_pixels(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_draw_player(t_cub *cub);
void	cub_draw_background(t_cub *cub);
void	cub_draw_minipx(t_cub *cub, int j, int i, int colour);
void	cub_draw_doors(t_cub *cub, t_ray *ray, int x);
void	cub_update_pixels(t_cub *cub, t_ray *ray, int x);
void	cub_calculate_door_distance(t_ray *ray);
void	cub_calculate_door_height(t_ray *ray);
int		cub_prep_wall_textures(t_cub *cub);
int		cub_prep_player_textures(t_cub *cub);
int		cub_prep_cow_textures(t_cub *cub);
int		cub_prep_horse_textures(t_cub *cub);
int		cub_prep_npc1_textures(t_cub *cub);
void	cub_draw_obj_in_front_doors(t_cub *cub);
void	cub_draw_obj_behind_doors(t_cub *cub);
void	cub_draw_cow(t_cub *cub, int x, t_sprite *sprite, int layer);
void	cub_draw_npc1(t_cub *cub, int x, t_sprite *sprite, int layer);
void	cub_draw_horse(t_cub *cub, int x, t_sprite *sprite, int layer);
void	cub_init_sprites(t_cub *cub, t_list **sprites);
int		cub_is_sprite(char c);
void	cub_update_sprite(t_cub *cub, t_sprite *sprite);
void	cub_calculate_sprite(t_cub *cub, t_sprite *sprite);

//ANIMATING functions
void	cub_update_cow_animation(t_cub *cub, double current_time);

//BUFFER CLEARING functions
void	cub_clear_image(mlx_image_t *img);
void	cub_clear_image_fast(mlx_image_t *img);

#endif