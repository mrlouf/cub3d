/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 16:33:35 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

void	cub_clean_wall_img(t_cub *cub)
{
	if (cub->w_images)
	{
		if (cub->mlx)
		{
			cub_delete_image(cub->mlx, &cub->w_images->no_i);
			cub_delete_image(cub->mlx, &cub->w_images->so_i);
			cub_delete_image(cub->mlx, &cub->w_images->ea_i);
			cub_delete_image(cub->mlx, &cub->w_images->we_i);
		}
		free(cub->w_images);
		cub->w_images = NULL;
	}
}

void	cub_clean_player_img(t_cub *cub)
{
	if (cub->player_img)
	{
		if (cub->mlx)
		{
			cub_delete_image(cub->mlx, &cub->player_img->p_1);
			cub_delete_image(cub->mlx, &cub->player_img->p_2);
			cub_delete_image(cub->mlx, &cub->player_img->p_3);
			cub_delete_image(cub->mlx, &cub->player_img->p_4);
		}
		free(cub->player_img);
		cub->player_img = NULL;
	}
}

void	cub_clean_mlx(t_cub *cub)
{
	if (cub->mlx)
	{
		if (cub->mini)
			cub_delete_image(cub->mlx, &cub->mini);
		if (cub->background_img)
			cub_delete_image(cub->mlx, &cub->background_img);
		if (cub->raycast_img)
			cub_delete_image(cub->mlx, &cub->raycast_img);
		if (cub->door_img)
			cub_delete_image(cub->mlx, &cub->door_img);
		if (cub->obj_img_f)
			cub_delete_image(cub->mlx, &cub->obj_img_f);
		if (cub->obj_img_b)
			cub_delete_image(cub->mlx, &cub->obj_img_b);
		mlx_terminate(cub->mlx);
		cub->mlx = NULL;
	}
}

void	cub_clean_textures(t_cub *cub)
{
	cub_delete_texture(&cub->icon);
	cub_delete_wall_txt(cub);
	cub_delete_player_txt(cub);
	cub_delete_cow_txt(cub);
	cub_delete_horse_txt(cub);
	cub_delete_npc1_txt(cub);
}

void	cub_clean(t_cub *cub)
{
	if (!cub)
		return ;
	cub_clean_strings(cub);
	if (cub->map)
		ft_free_narray((void **)cub->map, cub->rows);
	if (cub->zbuffer)
		free(cub->zbuffer);
	cub->map = NULL;
	cub_clean_textures(cub);
	cub_clean_wall_img(cub);
	cub_clean_player_img(cub);
	cub_clean_mlx(cub);
	cub_clean_sprite_list(cub);
	free(cub->player);
	cub->player = NULL;
	free(cub);
}
