/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 11:59:34 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/rendering.h"
#include "../../incs/parse.h"
#include "../../incs/utils.h"

static int	cub_get_player_txt(t_cub *cub)
{
	cub->player_txt->p_1 = mlx_load_png("./sprites/hands/p_1_390.png");
	if (!cub->player_txt->p_1)
		return (ft_putendl_fd(TEXT_P_ERR, 2), 1);
	cub->player_txt->p_2 = mlx_load_png("./sprites/hands/p_2_390.png");
	if (!cub->player_txt->p_2)
		return (ft_putendl_fd(TEXT_P_ERR, 2), 1);
	cub->player_txt->p_3 = mlx_load_png("./sprites/hands/p_3_390.png");
	if (!cub->player_txt->p_3)
		return (ft_putendl_fd(TEXT_P_ERR, 2), 1);
	cub->player_txt->p_4 = mlx_load_png("./sprites/hands/p_4_390.png");
	if (!cub->player_txt->p_4)
		return (ft_putendl_fd(TEXT_P_ERR, 2), 1);
	return (0);
}

void	cub_delete_player_txt(t_cub *cub)
{
	if (cub->player_txt)
	{
		if (cub->player_txt->p_1)
		{
			mlx_delete_texture(cub->player_txt->p_1);
			cub->player_txt->p_1 = NULL;
		}
		if (cub->player_txt->p_2)
		{
			mlx_delete_texture(cub->player_txt->p_2);
			cub->player_txt->p_2 = NULL;
		}
		if (cub->player_txt->p_3)
		{
			mlx_delete_texture(cub->player_txt->p_3);
			cub->player_txt->p_3 = NULL;
		}
		if (cub->player_txt->p_4)
		{
			mlx_delete_texture(cub->player_txt->p_4);
			cub->player_txt->p_4 = NULL;
		}
		free(cub->player_txt);
		cub->player_txt = NULL;
	}
}

static int	cub_prep_player_img(t_cub *cub)
{
	cub->player_img->p_1 = mlx_texture_to_image(cub->mlx, cub->player_txt->p_1);
	if (!cub->player_img->p_1)
		return (cub_delete_player_txt(cub), ft_putendl_fd(IMG_P_ERR, 2), 1);
	cub->player_img->p_2 = mlx_texture_to_image(cub->mlx, cub->player_txt->p_2);
	if (!cub->player_img->p_2)
		return (cub_delete_player_txt(cub), ft_putendl_fd(IMG_P_ERR, 2), 1);
	cub->player_img->p_3 = mlx_texture_to_image(cub->mlx, cub->player_txt->p_3);
	if (!cub->player_img->p_3)
		return (cub_delete_player_txt(cub), ft_putendl_fd(IMG_P_ERR, 2), 1);
	cub->player_img->p_4 = mlx_texture_to_image(cub->mlx, cub->player_txt->p_4);
	if (!cub->player_img->p_4)
		return (cub_delete_player_txt(cub), ft_putendl_fd(IMG_P_ERR, 2), 1);
	cub_delete_player_txt(cub);
	return (0);
}

int	cub_prep_player_textures(t_cub *cub)
{
	cub->player_txt = malloc(sizeof(t_player_txt));
	if (!cub->player_txt)
	{
		ft_putendl_fd(MEM_ERR, 2);
		return (1);
	}
	cub->player_img = malloc(sizeof(t_player_img));
	if (!cub->player_img)
	{
		ft_putendl_fd(MEM_ERR, 2);
		free(cub->player_txt);
		cub->player_txt = NULL;
		return (1);
	}
	if (cub_get_player_txt(cub))
	{
		cub_delete_player_txt(cub);
		return (free(cub->player_txt), free(cub->player_img), 1);
	}
	if (cub_prep_player_img(cub))
	{
		cub_delete_player_txt(cub);
		return (free(cub->player_txt), free(cub->player_img), 1);
	}
	return (0);
}
