/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:05:26 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/29 14:13:35 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

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
	{
		double olddx = cub->player->dir.x;
		cub->player->dir.x = cub->player->dir.x * cos(-cub->player->rotation) - cub->player->dir.y * sin(-cub->player->rotation);
		cub->player->dir.y = olddx * sin(-cub->player->rotation) + cub->player->dir.y * cos(-cub->player->rotation);
		double oldpx = cub->player->plane.x;
		cub->player->plane.x = cub->player->plane.x * cos(-cub->player->rotation) - cub->player->plane.y * sin(-cub->player->rotation);
		cub->player->plane.y = oldpx * sin(-cub->player->rotation) + cub->player->plane.y * cos(-cub->player->rotation);
		cub->player->angle -= cub->player->rotation;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		double olddx = cub->player->dir.x;
		cub->player->dir.x = cub->player->dir.x * cos(cub->player->rotation) - cub->player->dir.y * sin(cub->player->rotation);
		cub->player->dir.y = olddx * sin(cub->player->rotation) + cub->player->dir.y * cos(cub->player->rotation);
		double oldpx = cub->player->plane.x;
		cub->player->plane.x = cub->player->plane.x * cos(cub->player->rotation) - cub->player->plane.y * sin(cub->player->rotation);
		cub->player->plane.y = oldpx * sin(cub->player->rotation) + cub->player->plane.y * cos(cub->player->rotation);
		cub->player->angle += cub->player->rotation;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x * cub->player->speed)][(int)cub->player->pos.y] == 0)
			cub->player->pos.x += cub->player->dir.x * cub->player->speed;
		if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y + cub->player->dir.y * cub->player->speed)] == 0)
			cub->player->pos.y += cub->player->dir.y * cub->player->speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) && mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT))
	{
		if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x * cub->player->speed)][(int)cub->player->pos.y] == 0)
			cub->player->pos.x += cub->player->dir.x * cub->player->speed * 1.5;
		if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y + cub->player->dir.y * cub->player->speed)] == 0)
			cub->player->pos.y += cub->player->dir.y * cub->player->speed * 1.5;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x * cub->player->speed)][(int)cub->player->pos.y] == 0)
			cub->player->pos.x -= cub->player->dir.x * cub->player->speed;
		if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y + cub->player->dir.y * cub->player->speed)] == 0)
			cub->player->pos.y -= cub->player->dir.y * cub->player->speed;
	}
}
