/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_npc_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/05 16:31:09 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/rendering.h"
#include "../../incs/parse.h"
#include "../../incs/utils.h"

static int	cub_get_npc_1_txt(t_cub *cub)
{
	cub->npc_1_txt->npc_1_1 = mlx_load_png("./sprites/npcs/npc_1_1.png");
	if (!cub->npc_1_txt->npc_1_1)
		return (ft_putendl_fd(TEXT_NPC1_ERR, 2), 1);
	cub->npc_1_txt->height = 120;
	cub->npc_1_txt->width = 72;
	cub->npc_1_txt->pixels = cub->npc_1_txt->npc_1_1->pixels;
	return (0);
}

void	cub_delete_npc1_txt(t_cub *cub)
{
	if (cub->npc_1_txt)
	{
		if (cub->npc_1_txt->npc_1_1)
		{
			mlx_delete_texture(cub->npc_1_txt->npc_1_1);
			cub->npc_1_txt->npc_1_1 = NULL;
		}
		free(cub->npc_1_txt);
		cub->npc_1_txt = NULL;
	}
}

static int	cub_prep_npc_1_img(t_cub *cub)
{
	cub->npc_1_img->npc_1_1 = mlx_texture_to_image(cub->mlx, \
			cub->npc_1_txt->npc_1_1);
	if (!cub->npc_1_img->npc_1_1)
		return (cub_delete_npc1_txt(cub), ft_putendl_fd(IMG_NPC1_ERR, 2), 1);
	return (0);
}

int	cub_prep_npc1_textures(t_cub *cub)
{
	cub->npc_1_txt = malloc(sizeof(t_npc_1_txt));
	if (!cub->npc_1_txt)
	{
		ft_putendl_fd(MEM_ERR, 2);
		return (1);
	}
	cub->npc_1_img = malloc(sizeof(t_npc_1_img));
	if (!cub->npc_1_img)
	{
		ft_putendl_fd(MEM_ERR, 2);
		free(cub->npc_1_txt);
		cub->npc_1_txt = NULL;
		return (1);
	}
	if (cub_get_npc_1_txt(cub))
	{
		cub_delete_npc1_txt(cub);
		return (free(cub->npc_1_txt), free(cub->npc_1_img), 1);
	}
	if (cub_prep_npc_1_img(cub))
	{
		cub_delete_npc1_txt(cub);
		return (free(cub->npc_1_txt), free(cub->npc_1_img), 1);
	}
	return (0);
}
