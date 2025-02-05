/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/05 12:52:50 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

void	cub_clean_cow_img(t_cub *cub)
{
	if (cub->cow_img)
	{
		if (cub->mlx)
		{
			cub_delete_image(cub->mlx, &cub->cow_img->cow_1);
			cub_delete_image(cub->mlx, &cub->cow_img->cow_2);
		}
		free(cub->cow_img);
		cub->cow_img = NULL;
	}
}

void	cub_clean_horse_img(t_cub *cub)
{
	if (cub->horse_img)
	{
		if (cub->mlx)
		{
			cub_delete_image(cub->mlx, &cub->horse_img->horse_1);
		}
		free(cub->horse_img);
		cub->horse_img = NULL;
	}
}

void	cub_clean_npc1_img(t_cub *cub)
{
	if (cub->npc_1_img)
	{
		if (cub->mlx)
		{
			cub_delete_image(cub->mlx, &cub->npc_1_img->npc_1_1);
		}
		free(cub->npc_1_img);
		cub->npc_1_img = NULL;
	}
}

void	cub_clean_sprite_list(t_cub *cub)
{
	if (cub->sprites)
		ft_lstclear(&cub->sprites, free);
	cub->sprites = NULL;
	cub_clean_cow_img(cub);
	cub_clean_horse_img(cub);
	cub_clean_npc1_img(cub);
}
