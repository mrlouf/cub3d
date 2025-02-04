/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:33:01 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 16:53:15 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "cub3d.h"

typedef struct s_wall_txt
{
	mlx_texture_t	*no_t;
	mlx_texture_t	*so_t;
	mlx_texture_t	*ea_t;
	mlx_texture_t	*we_t;
	mlx_texture_t	*hand_1;
}	t_wall_txt;

typedef struct s_wall_img
{
	mlx_image_t	*no_i;
	mlx_image_t	*so_i;
	mlx_image_t	*ea_i;
	mlx_image_t	*we_i;
	mlx_image_t	*hand_1;
}	t_wall_img;

typedef struct s_player_txt
{
	mlx_texture_t	*p_1;
	mlx_texture_t	*p_2;
	mlx_texture_t	*p_3;
	mlx_texture_t	*p_4;
}	t_player_txt;

typedef struct s_player_img
{
	mlx_image_t	*p_1;
	mlx_image_t	*p_2;
	mlx_image_t	*p_3;
	mlx_image_t	*p_4;
}	t_player_img;

typedef struct s_cow_txt
{
	mlx_texture_t	*cow_1;
	mlx_texture_t	*cow_2;
	int				height;
	int				width;
	uint8_t			*pixels;
}	t_cow_txt;

typedef struct s_cow_img
{
	mlx_image_t	*cow_1;
	mlx_image_t	*cow_2;
}	t_cow_img;

typedef struct s_horse_txt
{
	mlx_texture_t	*horse_1;
	int				height;
	int				width;
	uint8_t			*pixels;
}	t_horse_txt;

typedef struct s_horse_img
{
	mlx_image_t	*horse_1;
}	t_horse_img;

#endif