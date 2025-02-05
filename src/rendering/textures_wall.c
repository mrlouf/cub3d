/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/05 15:44:47 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/rendering.h"
#include "../../incs/parse.h"
#include "../../incs/utils.h"

static int	cub_get_wall_txt(t_cub *cub)
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
	cub->w_textures->door = mlx_load_png("./textures/wolfenstein/door.png");
	if (!cub->w_textures->door)
		return (ft_putendl_fd(TEXT_LOAD_ERR_D, 2), 1);
	return (0);
}

void	cub_delete_wall_txt(t_cub *cub)
{
	if (cub->w_textures)
	{
		mlx_delete_texture(cub->w_textures->no_t);
		cub->w_textures->no_t = NULL;
		mlx_delete_texture(cub->w_textures->so_t);
		cub->w_textures->so_t = NULL;
		mlx_delete_texture(cub->w_textures->ea_t);
		cub->w_textures->ea_t = NULL;
		mlx_delete_texture(cub->w_textures->we_t);
		cub->w_textures->we_t = NULL;
		mlx_delete_texture(cub->w_textures->door);
		cub->w_textures->door = NULL;
		free(cub->w_textures);
		cub->w_textures = NULL;
	}
}

static int	cub_prep_wall_img(t_cub *cub)
{
	cub->w_images->no_i = mlx_texture_to_image(cub->mlx, cub->w_textures->no_t);
	if (!cub->w_images->no_i)
		return (cub_delete_wall_txt(cub), ft_putendl_fd(IMG_LOAD_ERR_N, 2), 1);
	cub->w_images->so_i = mlx_texture_to_image(cub->mlx, cub->w_textures->so_t);
	if (!cub->w_images->so_i)
		return (cub_delete_wall_txt(cub), ft_putendl_fd(IMG_LOAD_ERR_S, 2), 1);
	cub->w_images->ea_i = mlx_texture_to_image(cub->mlx, cub->w_textures->ea_t);
	if (!cub->w_images->ea_i)
		return (cub_delete_wall_txt(cub), ft_putendl_fd(IMG_LOAD_ERR_E, 2), 1);
	cub->w_images->we_i = mlx_texture_to_image(cub->mlx, cub->w_textures->we_t);
	if (!cub->w_images->we_i)
		return (cub_delete_wall_txt(cub), ft_putendl_fd(IMG_LOAD_ERR_W, 2), 1);
	cub->w_images->door = mlx_texture_to_image(cub->mlx, cub->w_textures->door);
	if (!cub->w_images->door)
		return (cub_delete_wall_txt(cub), ft_putendl_fd(IMG_LOAD_ERR_D, 2), 1);
	cub_delete_wall_txt(cub);
	return (0);
}

int	cub_prep_wall_textures(t_cub *cub)
{
	cub->w_textures = malloc(sizeof(t_wall_txt));
	if (!cub->w_textures)
	{
		ft_putendl_fd(MEM_ERR, 2);
		return (1);
	}
	cub->w_images = malloc(sizeof(t_wall_img));
	if (!cub->w_images)
	{
		ft_putendl_fd(MEM_ERR, 2);
		free(cub->w_textures);
		cub->w_textures = NULL;
		return (1);
	}
	if (cub_get_wall_txt(cub))
	{
		cub_delete_wall_txt(cub);
		return (free(cub->w_textures), free(cub->w_images), 1);
	}
	if (cub_prep_wall_img(cub))
	{
		cub_delete_wall_txt(cub);
		return (free(cub->w_textures), free(cub->w_images), 1);
	}
	return (0);
}
