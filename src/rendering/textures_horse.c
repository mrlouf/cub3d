/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_horse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 16:33:29 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/rendering.h"
#include "../../incs/parse.h"
#include "../../incs/utils.h"

static int	cub_get_horse_txt(t_cub *cub)
{
	cub->horse_txt->horse_1 = mlx_load_png("./sprites/animals/horse_1.png");
	if (!cub->horse_txt->horse_1)
		return (ft_putendl_fd(TEXT_HORSE_ERR, 2), 1);
	cub->horse_txt->height = 130;
	cub->horse_txt->width = 144;
	cub->horse_txt->pixels = cub->horse_txt->horse_1->pixels;
	return (0);
}

void	cub_delete_horse_txt(t_cub *cub)
{
	if (cub->horse_txt)
	{
		if (cub->horse_txt->horse_1)
		{
			mlx_delete_texture(cub->horse_txt->horse_1);
			cub->horse_txt->horse_1 = NULL;
		}
		free(cub->horse_txt);
		cub->horse_txt = NULL;
	}
}

static int	cub_prep_horse_img(t_cub *cub)
{
	cub->horse_img->horse_1 = mlx_texture_to_image(cub->mlx, \
			cub->horse_txt->horse_1);
	if (!cub->horse_img->horse_1)
		return (cub_delete_horse_txt(cub), ft_putendl_fd(IMG_HORSE_ERR, 2), 1);
	return (0);
}

int	cub_prep_horse_textures(t_cub *cub)
{
	cub->horse_txt = malloc(sizeof(t_horse_txt));
	if (!cub->horse_txt)
	{
		ft_putendl_fd(MEM_ERR, 2);
		return (1);
	}
	cub->horse_img = malloc(sizeof(t_horse_img));
	if (!cub->horse_img)
	{
		ft_putendl_fd(MEM_ERR, 2);
		free(cub->horse_txt);
		cub->horse_txt = NULL;
		return (1);
	}
	if (cub_get_horse_txt(cub))
	{
		cub_delete_horse_txt(cub);
		return (free(cub->horse_txt), free(cub->horse_img), 1);
	}
	if (cub_prep_horse_img(cub))
	{
		cub_delete_horse_txt(cub);
		return (free(cub->horse_txt), free(cub->horse_img), 1);
	}
	return (0);
}
