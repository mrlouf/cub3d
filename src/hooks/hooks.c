/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:05:26 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 10:53:43 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

/*
	Opens and closes doors with a 0.5 second cooldown in-between to avoid
	interacting too quickly.
	TODO
	implement sprite animation.
*/
void	cub_open_close_doors(t_cub *cub)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - cub->toggle_door.tv_sec) \
		* 1000000L + (current_time.tv_usec - cub->toggle_door.tv_usec);
	if (elapsed_time < COOLDOWN_PERIOD)
		return ;
	if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed * 7)][(int)cub->player->pos.y] == 2)
		cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed * 7)][(int)cub->player->pos.y] = -1;
	else if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed * 7)][(int)cub->player->pos.y] == -1)
		cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* cub->player->speed * 7)][(int)cub->player->pos.y] = 2;
	else if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed * 7)] == 2)
		(cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed * 7)] = -1);
	else if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed * 7)] == -1)
		(cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * cub->player->speed * 7)] = 2);
	gettimeofday(&cub->toggle_door, NULL);
}

/*
	Rotates the player to the right by changing its direction,
	but also the plane to keep the same POV.
*/
void	cub_rotate_right(t_cub *cub, double nerf)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->player->dir.x;
	oldplanex = cub->player->plane.x;
	cub->player->dir.x = cub->player->dir.x \
		* cos(-cub->player->rotation * nerf) \
		- cub->player->dir.y * sin(-cub->player->rotation * nerf);
	cub->player->dir.y = olddirx * sin(-cub->player->rotation * nerf) \
		+ cub->player->dir.y * cos(-cub->player->rotation * nerf);
	cub->player->plane.x = cub->player->plane.x \
		* cos(-cub->player->rotation * nerf) \
		- cub->player->plane.y * sin(-cub->player->rotation * nerf);
	cub->player->plane.y = oldplanex * sin(-cub->player->rotation * nerf) \
		+ cub->player->plane.y * cos(-cub->player->rotation * nerf);
	cub->player->angle -= cub->player->rotation * nerf;
}

/*
	Rotates the player to the left by changing its direction,
	but also the plane to keep the camera pointed and keep the same POV.
*/
void	cub_rotate_left(t_cub *cub, double nerf)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->player->dir.x;
	oldplanex = cub->player->plane.x;
	cub->player->dir.x = cub->player->dir.x \
		* cos(cub->player->rotation * nerf) \
		- cub->player->dir.y * sin(cub->player->rotation * nerf);
	cub->player->dir.y = olddirx * sin(cub->player->rotation * nerf) \
		+ cub->player->dir.y * cos(cub->player->rotation * nerf);
	cub->player->plane.x = cub->player->plane.x \
		* cos(cub->player->rotation * nerf) \
		- cub->player->plane.y * sin(cub->player->rotation * nerf);
	cub->player->plane.y = oldplanex * sin(cub->player->rotation * nerf) \
		+ cub->player->plane.y * cos(cub->player->rotation * nerf);
	cub->player->angle += cub->player->rotation * nerf;
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
	cub_pet(cub);
}
