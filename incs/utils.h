/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:33:01 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 12:46:48 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

void	cub_dda(t_cub *cub, t_vector start, t_vector end, int colour);

void	cub_clean(t_cub *cub);
void	cub_clean_textures(t_cub *cub);
void	cub_clean_mlx(t_cub *cub);
void	cub_clean_player_img(t_cub *cub);
void	cub_clean_wall_img(t_cub *cub);
void	cub_clean_cow_img(t_cub *cub);
void	cub_clean_strings(t_cub *cub);
void	cub_delete_texture(mlx_texture_t **texture);
void	cub_delete_image(mlx_t *mlx, mlx_image_t **image);
void	cub_delete_wall_txt(t_cub *cub);
void	cub_delete_player_txt(t_cub *cub);
void	cub_delete_cow_txt(t_cub *cub);
void	cub_delete_horse_txt(t_cub *cub);
void	cub_delete_npc1_txt(t_cub *cub);
void	cub_clean_sprite_list(t_cub *cub);

void	cub_select_sprite(t_cub *cub, int x, t_sprite *sprite, int layer);
void	cub_get_sprite_width(t_cub *cub, t_sprite *sprite);
void	cub_sort_sprites(t_list **sprites);

#endif