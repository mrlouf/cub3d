/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:05:26 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 10:46:39 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

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
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		cub_move_right(cub, cub->player->speed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		cub_move_left(cub, cub->player->speed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		cub_move_forward(cub, cub->player->speed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) \
		&& mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT))
		cub_move_forward(cub, cub->player->speed * 1.5);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub_move_backward(cub);
}
