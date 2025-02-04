/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:05:26 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 17:44:06 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

/*
	Opens and closes doors. This needs to be time-based instead of frames,
	so that there is a cooldown between opening and closing.
	TODO
	Implement sprite animation when opening and closing.
*/
void	cub_open_close_doors(t_cub *cub)
{
	if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed)][(int)cub->player->pos.y] == 2)
		cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed)][(int)cub->player->pos.y] = -1;
	else if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed)][(int)cub->player->pos.y] == -1)
		cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed)][(int)cub->player->pos.y] = 2;
	else if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed)] == 2)
		(cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed)] = -1);
	else if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed)] == -1)
		(cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed)] = 2);
}

/*
	Rotates the player to the right by changing its direction,
	but also the plane to keep the same POV.
*/
void	cub_rotate_right(t_cub *cub)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->player->dir.x;
	oldplanex = cub->player->plane.x;
	cub->player->dir.x = cub->player->dir.x * cos(-cub->player->rotation) \
		- cub->player->dir.y * sin(-cub->player->rotation);
	cub->player->dir.y = olddirx * sin(-cub->player->rotation) \
		+ cub->player->dir.y * cos(-cub->player->rotation);
	cub->player->plane.x = cub->player->plane.x * cos(-cub->player->rotation) \
		- cub->player->plane.y * sin(-cub->player->rotation);
	cub->player->plane.y = oldplanex * sin(-cub->player->rotation) \
		+ cub->player->plane.y * cos(-cub->player->rotation);
	cub->player->angle -= cub->player->rotation;
}

/*
	Rotates the player to the left by changing its direction,
	but also the plane to keep the camera pointed and keep the same POV.
*/
void	cub_rotate_left(t_cub *cub)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->player->dir.x;
	oldplanex = cub->player->plane.x;
	cub->player->dir.x = cub->player->dir.x * cos(cub->player->rotation) \
		- cub->player->dir.y * sin(cub->player->rotation);
	cub->player->dir.y = olddirx * sin(cub->player->rotation) \
		+ cub->player->dir.y * cos(cub->player->rotation);
	cub->player->plane.x = cub->player->plane.x * cos(cub->player->rotation) \
		- cub->player->plane.y * sin(cub->player->rotation);
	cub->player->plane.y = oldplanex * sin(cub->player->rotation) \
		+ cub->player->plane.y * cos(cub->player->rotation);
	cub->player->angle += cub->player->rotation;
}

/*
	Primary function to catch the various hooks and execute the associated
	action (eg. pressing ESC closes the window).
*/
void	cub_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_ADD))
		if (cub->minimap_px < 10)
			cub->minimap_px++;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_SUBTRACT))
		if (cub->minimap_px > 1)
			cub->minimap_px--;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_SPACE))
		cub_open_close_doors(cub);
	cub_movements(cub);
}
