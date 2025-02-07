/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_cow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 18:46:35 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/rendering.h"
#include "../../incs/parse.h"
#include "../../incs/utils.h"

static int	cub_get_cow_txt(t_cub *cub)
{
	cub->cow_txt->cow_1 = mlx_load_png("./sprites/animals/cow_1.png");
	cub->cow_txt->cow_2 = mlx_load_png("./sprites/animals/cow_2.png");
	cub->cow_txt->cow_3 = mlx_load_png("./sprites/animals/cow_3.png");
	cub->cow_txt->cow_4 = mlx_load_png("./sprites/animals/cow_4.png");
	cub->cow_txt->cow_5 = mlx_load_png("./sprites/animals/cow_5.png");
	cub->cow_txt->cow_6 = mlx_load_png("./sprites/animals/cow_6.png");
	if (!cub->cow_txt->cow_1 || !cub->cow_txt->cow_2 || !cub->cow_txt->cow_3
		|| !cub->cow_txt->cow_4 || !cub->cow_txt->cow_5 || !cub->cow_txt->cow_6)
		return (ft_putendl_fd(TEXT_COW_ERR, 2), 1);
	cub->cow_txt->height = 75;
	cub->cow_txt->width = 120;
	cub->cow_txt->pixels = cub->cow_txt->cow_1->pixels;
	cub->cow_txt->current_frame = 0;
	cub->cow_txt->last_frame_time = 0;
	cub->cow_txt->frame_duration = 1.0;
	return (0);
}

void	cub_delete_cow_txt(t_cub *cub)
{
	if (cub->cow_txt)
	{
		mlx_delete_texture(cub->cow_txt->cow_1);
		cub->cow_txt->cow_1 = NULL;
		mlx_delete_texture(cub->cow_txt->cow_2);
		cub->cow_txt->cow_2 = NULL;
		mlx_delete_texture(cub->cow_txt->cow_3);
		cub->cow_txt->cow_3 = NULL;
		mlx_delete_texture(cub->cow_txt->cow_4);
		cub->cow_txt->cow_4 = NULL;
		mlx_delete_texture(cub->cow_txt->cow_5);
		cub->cow_txt->cow_5 = NULL;
		mlx_delete_texture(cub->cow_txt->cow_6);
		cub->cow_txt->cow_6 = NULL;
		free(cub->cow_txt);
		cub->cow_txt = NULL;
	}
}

static int	cub_prep_cow_img(t_cub *cub)
{
	cub->cow_img->cow_1 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_1);
	cub->cow_img->cow_2 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_2);
	cub->cow_img->cow_3 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_3);
	cub->cow_img->cow_4 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_4);
	cub->cow_img->cow_5 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_5);
	cub->cow_img->cow_6 = mlx_texture_to_image(cub->mlx, cub->cow_txt->cow_6);
	if (!cub->cow_img->cow_1 || !cub->cow_img->cow_2 || !cub->cow_img->cow_3
		|| !cub->cow_img->cow_4 || !cub->cow_img->cow_5 || !cub->cow_img->cow_6)
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
