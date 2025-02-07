/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:40:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/06 15:02:52 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/hooks.h"

/*
	Moves the player forward after having done a preliminary collision check
	so as to not collide with any wall.
*/
void	cub_move_backward(t_cub *cub)
{
	if (cub->map[(int)(cub->player->pos.x - cub->player->dir.x \
		* cub->player->speed)][(int)cub->player->pos.y] < 1)
		cub->player->pos.x -= cub->player->dir.x * cub->player->speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		- cub->player->dir.y * cub->player->speed)] < 1)
		cub->player->pos.y -= cub->player->dir.y * cub->player->speed;
}

/*
	Moves the player forward after having done a preliminary collision check
	so as to not collide with any wall. Takes a second parameter
	to set the speed to walk or sprint.
*/
void	cub_move_forward(t_cub *cub, double speed)
{
	if (cub->map[(int)(cub->player->pos.x + cub->player->dir.x \
		* speed)][(int)cub->player->pos.y] < 1)
		cub->player->pos.x += cub->player->dir.x * speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * speed)] < 1)
		cub->player->pos.y += cub->player->dir.y * speed;
}

/*
	Moves the player to the left after having done a collision check
	so as to not collide with any wall.
*/
void	cub_move_left(t_cub *cub, double speed)
{
	if (cub->map[(int)(cub->player->pos.x + -cub->player->dir.y \
		* speed)][(int)cub->player->pos.y] < 1)
		cub->player->pos.x += -cub->player->dir.y * speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.x * speed)] < 1)
		cub->player->pos.y += cub->player->dir.x * speed;
}

/*
	Moves the player to the right after having done a collision check
	so as to not collide with any wall.
*/
void	cub_move_right(t_cub *cub, double speed)
{
	if (cub->map[(int)(cub->player->pos.x + cub->player->dir.y \
		* speed)][(int)cub->player->pos.y] < 1)
		cub->player->pos.x += cub->player->dir.y * speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ -cub->player->dir.x * speed)] < 1)
		cub->player->pos.y += -cub->player->dir.x * speed;
}

/*
	This function regroups the hooks for the player's movements
	and rotations.
*/
void	cub_movements(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		cub_move_right(cub, cub->player->speed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		cub_move_left(cub, cub->player->speed);
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_W) \
		&& mlx_is_key_down(cub->mlx, MLX_KEY_A)) \
		|| (mlx_is_key_down(cub->mlx, MLX_KEY_W) \
		&& mlx_is_key_down(cub->mlx, MLX_KEY_D)))
		cub_move_forward(cub, cub->player->speed * 0.33);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_W) \
		&& mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT))
		cub_move_forward(cub, cub->player->speed * 1.5);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		cub_move_forward(cub, cub->player->speed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub_move_backward(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub_rotate_left(cub, 2.0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub_rotate_right(cub, 2.0);
}
