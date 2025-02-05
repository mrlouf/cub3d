/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_cow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 14:10:05 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/rendering.h"
#include "../../incs/parse.h"
#include "../../incs/utils.h"

static int	cub_get_cow_txt(t_cub *cub)
{
	cub->cow_txt->cow_1 = mlx_load_png("./sprites/animals/cow_1.png");
	if (!cub->cow_txt->cow_1)
		return (ft_putendl_fd(TEXT_COW_ERR, 2), 1);
	cub->cow_txt->cow_2 = mlx_load_png("./sprites/animals/cow_2.png");
	if (!cub->cow_txt->cow_2)
		return (ft_putendl_fd(TEXT_COW_ERR, 2), 1);
	cub->cow_txt->height = 96;
	cub->cow_txt->width = 144;
	cub->cow_txt->pixels = cub->cow_txt->cow_1->pixels;
	return (0);
}

void	cub_delete_cow_txt(t_cub *cub)
{
	if (cub->cow_txt)
	{
		if (cub->cow_txt->cow_1)
		{
			mlx_delete_texture(cub->cow_txt->cow_1);
			cub->cow_txt->cow_1 = NULL;
		}
		if (cub->cow_txt->cow_2)
		{
			mlx_delete_texture(cub->cow_txt->cow_2);
			cub->cow_txt->cow_2 = NULL;
		}
		free(cub->cow_txt);
		cub->cow_txt = NULL;
	}
}

static int	cub_prep_cow_img(t_cub *cub)
{
	cub->cow_img->cow_1 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_1);
	if (!cub->cow_img->cow_1)
		return (cub_delete_cow_txt(cub), ft_putendl_fd(IMG_COW_ERR, 2), 1);
	cub->cow_img->cow_2 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_2);
	if (!cub->cow_img->cow_2)
		return (cub_delete_cow_txt(cub), ft_putendl_fd(IMG_COW_ERR, 2), 1);
	return (0);
}

int	cub_prep_cow_textures(t_cub *cub)
{
	cub->cow_txt = malloc(sizeof(t_cow_txt));
	if (!cub->cow_txt)
	{
		ft_putendl_fd(MEM_ERR, 2);
		return (1);
	}
	cub->cow_img = malloc(sizeof(t_cow_img));
	if (!cub->cow_img)
	{
		ft_putendl_fd(MEM_ERR, 2);
		free(cub->cow_txt);
		cub->cow_txt = NULL;
		return (1);
	}
	if (cub_get_cow_txt(cub))
	{
		cub_delete_cow_txt(cub);
		return (free(cub->cow_txt), free(cub->cow_img), 1);
	}
	if (cub_prep_cow_img(cub))
	{
		cub_delete_cow_txt(cub);
		return (free(cub->cow_txt), free(cub->cow_img), 1);
	}
	return (0);
}
