/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:37:16 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 11:01:37 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/init.h"
#include "../../incs/parse.h"

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

static int	cub_init_img_buffers(t_cub *cub)
{
	cub->background_img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->background_img)
		return (1);
	mlx_image_to_window(cub->mlx, cub->background_img, 0, 0);
	cub->raycast_img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->raycast_img)
		return (1);
	mlx_image_to_window(cub->mlx, cub->raycast_img, 0, 0);
	cub->obj_img_b = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->obj_img_b)
		return (1);
	mlx_image_to_window(cub->mlx, cub->obj_img_b, 0, 0);
	cub->door_img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->door_img)
		return (1);
	mlx_image_to_window(cub->mlx, cub->door_img, 0, 0);
	cub->obj_img_f = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->obj_img_f)
		return (1);
	mlx_image_to_window(cub->mlx, cub->obj_img_f, 0, 0);
	cub->mini = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->mini)
		return (1);
	mlx_image_to_window(cub->mlx, cub->mini, 0, 0);
	return (0);
}

static void	cub_init_null(t_cub *cub)
{
	cub->map = NULL;
	cub->no_t = NULL;
	cub->so_t = NULL;
	cub->ea_t = NULL;
	cub->we_t = NULL;
	cub->w_textures = NULL;
	cub->w_images = NULL;
	cub->player_txt = NULL;
	cub->player_img = NULL;
	cub->cow_txt = NULL;
	cub->cow_img = NULL;
	cub->horse_txt = NULL;
	cub->horse_img = NULL;
	cub->npc_1_txt = NULL;
	cub->npc_1_img = NULL;
	cub->mini = NULL;
	cub->sprites = NULL;
}

int	cub_init(t_cub *cub, char **av)
{
	cub_init_null(cub);
	cub->filename = ft_strdup(av[1]);
	if (!cub->filename)
		return (1);
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	if (!cub->mlx)
		return (1);
	cub->icon = mlx_load_png("./src/utils/icon.png");
	cub->minimap_px = 10;
	cub->zbuffer = malloc(sizeof(t_zbuffer) * WINDOW_WIDTH);
	if (!cub->zbuffer)
		return (ft_putendl_fd(MEM_ERR, 2), 1);
	if (cub_init_img_buffers(cub))
		return (1);
	if (cub_player_init(cub))
		return (1);
	return (0);
}
