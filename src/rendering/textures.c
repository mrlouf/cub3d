/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 14:24:56 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/rendering.h"
#include "../../incs/parse.h"
#include "../../incs/utils.h"

static int	cub_get_textures(t_cub *cub)
{
	cub->w_textures->no_t = mlx_load_png(cub->no_t);
	if (!cub->w_textures->no_t)
		return (ft_putendl_fd(TEXT_LOAD_ERR_N, 2), 1);
	cub->w_textures->so_t = mlx_load_png(cub->so_t);
	if (!cub->w_textures->so_t)
		return (ft_putendl_fd(TEXT_LOAD_ERR_S, 2), 1);
	cub->w_textures->ea_t = mlx_load_png(cub->ea_t);
	if (!cub->w_textures->ea_t)
		return (ft_putendl_fd(TEXT_LOAD_ERR_E, 2), 1);
	cub->w_textures->we_t = mlx_load_png(cub->we_t);
	if (!cub->w_textures->we_t)
		return (ft_putendl_fd(TEXT_LOAD_ERR_W, 2), 1);
	return (0);
}

void	cub_delete_textures(t_cub *cub)
{
	if (cub->w_textures)
	{
		if (cub->w_textures->no_t)
		{
			mlx_delete_texture(cub->w_textures->no_t);
			cub->w_textures->no_t = NULL;
		}
		if (cub->w_textures->so_t)
		{
			mlx_delete_texture(cub->w_textures->so_t);
			cub->w_textures->so_t = NULL;
		}
		if (cub->w_textures->ea_t)
		{
			mlx_delete_texture(cub->w_textures->ea_t);
			cub->w_textures->ea_t = NULL;
		}
		if (cub->w_textures->we_t)
		{
			mlx_delete_texture(cub->w_textures->we_t);
			cub->w_textures->we_t = NULL;
		}
		free(cub->w_textures);
		cub->w_textures = NULL;
	}
}

static int	cub_prep_images(t_cub *cub)
{
	cub->w_images->no_i = mlx_texture_to_image(cub->mlx, cub->w_textures->no_t);
	if (!cub->w_images->no_i)
		return (cub_delete_textures(cub), ft_putendl_fd(IMG_LOAD_ERR_N, 2), 1);
	cub->w_images->so_i = mlx_texture_to_image(cub->mlx, cub->w_textures->so_t);
	if (!cub->w_images->so_i)
		return (cub_delete_textures(cub), ft_putendl_fd(IMG_LOAD_ERR_S, 2), 1);
	cub->w_images->ea_i = mlx_texture_to_image(cub->mlx, cub->w_textures->ea_t);
	if (!cub->w_images->ea_i)
		return (cub_delete_textures(cub), ft_putendl_fd(IMG_LOAD_ERR_E, 2), 1);
	cub->w_images->we_i = mlx_texture_to_image(cub->mlx, cub->w_textures->we_t);
	if (!cub->w_images->we_i)
		return (cub_delete_textures(cub), ft_putendl_fd(IMG_LOAD_ERR_W, 2), 1);
	cub_delete_textures(cub);
	return (0);
}

int	cub_prep_wall_textures(t_cub *cub)
{
	cub->w_textures = malloc(sizeof(t_textures));
	if (!cub->w_textures)
	{
		ft_putendl_fd(MEM_ERR, 2);
		return (1);
	}
	cub->w_images = malloc(sizeof(t_images));
	if (!cub->w_images)
	{
		ft_putendl_fd(MEM_ERR, 2);
		free(cub->w_textures);
		cub->w_textures = NULL;
		return (1);
	}
	if (cub_get_textures(cub))
	{
		cub_delete_textures(cub);
		return (free(cub->w_textures), free(cub->w_images), 1);
	}
	if (cub_prep_images(cub))
	{
		cub_delete_textures(cub);
		return (free(cub->w_textures), free(cub->w_images), 1);
	}
	return (0);
}
