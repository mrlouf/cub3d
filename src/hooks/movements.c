/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:40:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 15:54:09 by nponchon         ###   ########.fr       */
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
		* cub->player->speed)][(int)cub->player->pos.y] == 0)
		cub->player->pos.x -= cub->player->dir.x * cub->player->speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		- cub->player->dir.y * cub->player->speed)] == 0)
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
		* speed)][(int)cub->player->pos.y] == 0)
		cub->player->pos.x += cub->player->dir.x * speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.y * speed)] == 0)
		cub->player->pos.y += cub->player->dir.y * speed;
}

/*
	Moves the player to the left after having done a collision check
	so as to not collide with any wall.
*/
void	cub_move_left(t_cub *cub, double speed)
{
	if (cub->map[(int)(cub->player->pos.x + -cub->player->dir.y \
		* speed)][(int)cub->player->pos.y] == 0)
		cub->player->pos.x += -cub->player->dir.y * speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ cub->player->dir.x * speed)] == 0)
		cub->player->pos.y += cub->player->dir.x * speed;
}

/*
	Moves the player to the right after having done a collision check
	so as to not collide with any wall.
*/
void	cub_move_right(t_cub *cub, double speed)
{
	if (cub->map[(int)(cub->player->pos.x + cub->player->dir.y \
		* speed)][(int)cub->player->pos.y] == 0)
		cub->player->pos.x += cub->player->dir.y * speed;
	if (cub->map[(int)cub->player->pos.x][(int)(cub->player->pos.y \
		+ -cub->player->dir.x * speed)] == 0)
		cub->player->pos.y += -cub->player->dir.x * speed;
}
