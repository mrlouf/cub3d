/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:41:12 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 12:19:05 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"

#include <math.h>
#include <stdlib.h>

/*
	Initialises a single ray with basic information needed to compute
	the distance to the wall later like the direction, position and delta.
*/
static void	cub_init_ray(t_ray *ray, int x, t_player *player)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir_x = \
		player->dir.x + player->plane.x * ray->camera_x;
	ray->dir_y = \
		player->dir.y + player->plane.y * ray->camera_x;
	ray->map_x = (int)player->pos.x;
	ray->map_y = (int)player->pos.y;
	if (ray->dir_x == 0)
		ray->delta_dx = INFINITY;
	else
		ray->delta_dx = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dy = INFINITY;
	else
		ray->delta_dy = fabs(1 / ray->dir_y);
	ray->door_hit = 0;
}

/*
	Calculates the step of each ray.
*/
static void	cub_calculate_step(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sided_x = (player->pos.x - ray->map_x) * ray->delta_dx;
	}
	else
	{
		ray->step_x = 1;
		ray->sided_x = (ray->map_x + 1.0 - player->pos.x) * ray->delta_dx;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sided_y = (player->pos.y - ray->map_y) * ray->delta_dy;
	}
	else
	{
		ray->step_y = 1;
		ray->sided_y = (ray->map_y + 1.0 - player->pos.y) * ray->delta_dy;
	}
}

/*
	Uses the side distances x and y from the ray to compare with the map
	to check for a potential collision with a wall.
	!A non-closed map leads to infinite calculation > OVERFLOW!
*/
static void	cub_calculate_wall_distance(t_ray *ray, int **map)
{
	while (42)
	{
		if (ray->sided_x < ray->sided_y)
		{
			ray->sided_x += ray->delta_dx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sided_y += ray->delta_dy;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_x][ray->map_y] == -3)
		{
			ray->door_hit = 1;
			if (ray->side == 0)
				ray->door_d = (ray->sided_x - (ray->delta_dx / 2));
			else
				ray->door_d = (ray->sided_y - (ray->delta_dy / 2));
		}
		else if (map[ray->map_x][ray->map_y] > 0)
			break ;
	}
	if (ray->side == 0)
		ray->wall_d = (ray->sided_x - (ray->delta_dx));
	else
		ray->wall_d = (ray->sided_y - (ray->delta_dy));
}

/*
	Using the distance to the wall, calculates the height (ie. the vertical size)
	of the ray to be drawn, which gives the start and end points of the ray,
	that are rounded up to zero or down to WIN_SIZE to avoid pixels out of bound.
*/
static void	cub_calculate_wall_height(t_ray *ray)
{
	ray->wall_h = (int)WINDOW_HEIGHT / ray->wall_d;
	ray->start = -ray->wall_h / 2 + WINDOW_HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->wall_h / 2 + WINDOW_HEIGHT / 2;
	if (ray->end >= WINDOW_HEIGHT)
		ray->end = WINDOW_HEIGHT;
	if (ray->door_hit)
	{
		ray->door_h = (int)WINDOW_HEIGHT / ray->door_d;
		ray->dstart = -ray->door_h / 2 + WINDOW_HEIGHT / 2;
		if (ray->dstart < 0)
			ray->dstart = 0;
		ray->dend = ray->door_h / 2 + WINDOW_HEIGHT / 2;
		if (ray->dend >= WINDOW_HEIGHT)
			ray->dend = WINDOW_HEIGHT;
	}
}

static void	cub_draw_doors(t_cub *cub, t_ray *ray, int x)
{
	//t_texture_data	data;
	//double			tex_pos;
	int				i;

	//set_texture_and_wall(&data, cub, ray);
	//calculate_texture_position(&data, ray);
	//tex_pos = (ray->dstart - WINDOW_HEIGHT / 2
	//		+ (ray->dend - ray->dstart) / 2) * data.step;
	i = ray->dstart;
	while (i < ray->dend)
	{
	//	data.tex_y = (int)tex_pos & (data.texture->height - 1);
	//	tex_pos += data.step;
		mlx_put_pixel(cub->img, x, i++,
			0xFF0000FF);
	}
}

/*
	The incredible ray-casting machinery.
	It calculates each ray needed depending on the FOV, then the step,
	wall distance and wall height of the ray before updating the pixels.
*/
int	cub_raycasting(t_cub *cub, t_ray *ray)
{
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cub_init_ray(ray, x, cub->player);
		cub_calculate_step(ray, cub->player);
		cub_calculate_wall_distance(ray, cub->map);
		cub_calculate_wall_height(ray);
		cub_update_pixels(cub, ray, x);
		if (ray->door_hit && (ray->door_d < ray->wall_d))
			cub_draw_doors(cub, ray, x);
		x++;
	}
	return (0);
}
