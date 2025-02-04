/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:33:01 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 10:50:25 by hmunoz-g         ###   ########.fr       */
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
void	cub_clean_strings(t_cub *cub);
void	cub_delete_texture(mlx_texture_t **texture);
void	cub_delete_image(mlx_t *mlx, mlx_image_t **image);

#endif