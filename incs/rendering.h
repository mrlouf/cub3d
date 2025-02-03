/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:39:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 09:36:40 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include <math.h>
# include "cub3d.h"

void	cub_loop(void *param);
int		cub_init_pixels(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_draw_background(t_cub *cub);
int		cub_prep_wall_textures(t_cub *cub);

#endif