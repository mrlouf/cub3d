/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 10:50:19 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

void	cub_delete_image(mlx_t *mlx, mlx_image_t **image)
{
	if (*image)
	{
		mlx_delete_image(mlx, *image);
		*image = NULL;
	}
}

void	cub_delete_texture(mlx_texture_t **texture)
{
	if (*texture)
	{
		mlx_delete_texture(*texture);
		*texture = NULL;
	}
}

void	cub_clean_strings(t_cub *cub)
{
	free(cub->filename);
	cub->filename = NULL;
	free(cub->no_t);
	cub->no_t = NULL;
	free(cub->so_t);
	cub->so_t = NULL;
	free(cub->ea_t);
	cub->ea_t = NULL;
	free(cub->we_t);
	cub->we_t = NULL;
}
