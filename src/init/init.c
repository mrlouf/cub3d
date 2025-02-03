/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:37:16 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 11:27:24 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/init.h"
#include "math.h"

/*
	Initialises the camera once the direction of the player has been established
	from parsing the map. Also init the angle for drawing the FOV.
*/
void	cub_camera_init(t_cub *cub)
{
	if ((cub->player->dir.x == 0 && fabs(cub->player->dir.y) == 1))
	{
		cub->player->plane.x = 0.66 * cub->player->dir.y;
		cub->player->plane.y = 0;
	}
	else
	{
		cub->player->plane.x = 1.0E-30;
		cub->player->plane.y = -0.66;
		if (cub->player->dir.y == 0 && cub->player->dir.x == -1)
			cub->player->plane.y = -cub->player->plane.y;
	}
	cub->player->angle = atan2(cub->player->dir.y, cub->player->dir.x);
}

static int	cub_player_init(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (1);
	cub->player->speed = 0.10;
	cub->player->rotation = 0.05;
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
	cub->minimap_px = 10;
	if (cub_player_init(cub))
		return (1);
	return (0);
}
