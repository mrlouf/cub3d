/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:37:16 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 12:34:32 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/init.h"
#include "math.h"

static int	cub_player_init(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (1);
	cub->player->plane.x = 0;
	cub->player->plane.y = -0.66;
	cub->player->speed = 0.10;
	cub->player->rotation = 0.05;
	cub->player->angle = atan2(cub->player->dir.y, cub->player->dir.x);
	return (0);
}

int	cub_init(t_cub *cub, char **av)
{
	cub->map = NULL;
	cub->no_t = NULL;
	cub->so_t = NULL;
	cub->ea_t = NULL;
	cub->we_t = NULL;
	cub->w_textures = NULL;
	cub->w_images = NULL;
	cub->filename = ft_strdup(av[1]);
	if (!cub->filename)
		return (1);
	cub->img = NULL;
	cub->mlx = NULL;
	cub->icon = mlx_load_png("./src/utils/icon.png");
	cub->minimap_px = 2;
	if (cub_player_init(cub))
		return (1);
	return (0);
}
