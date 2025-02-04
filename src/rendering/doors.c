/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:31:52 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 17:08:45 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"

void	cub_calculate_door_texture(t_texture_data *data, t_ray *ray)
{
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * data->texture->width);
	data->step = (double)data->texture->height / (ray->dend - ray->dstart);
}

void	cub_calculate_door_height(t_ray *ray)
{
	ray->door_h = (int)WINDOW_HEIGHT / ray->door_d;
	ray->dstart = -ray->door_h / 2 + WINDOW_HEIGHT / 2;
	if (ray->dstart < 0)
		ray->dstart = 0;
	ray->dend = ray->door_h / 2 + WINDOW_HEIGHT / 2;
	if (ray->dend >= WINDOW_HEIGHT)
		ray->dend = WINDOW_HEIGHT;
}

void	cub_calculate_door_distance(t_ray *ray)
{
	ray->door_hit = 1;
	ray->dside = ray->side;
	if (ray->side == 0)
		ray->door_d = (ray->sided_x - (ray->delta_dx / 2));
	else
		ray->door_d = (ray->sided_y - (ray->delta_dy / 2));
}

void	cub_set_texture_door(t_texture_data *data, t_cub *cub, t_ray *ray)
{
	data->texture = cub->w_images->we_i;
	if (ray->dside == 0)
		data->wall_x = cub->player->pos.y + ray->door_d * ray->dir_y;
	else
		data->wall_x = cub->player->pos.x + ray->door_d * ray->dir_x;
}

void	cub_draw_doors(t_cub *cub, t_ray *ray, int x)
{
	t_texture_data	data;
	double			tex_pos;
	int				i;

	cub_set_texture_door(&data, cub, ray);
	cub_calculate_door_texture(&data, ray);
	tex_pos = (ray->dstart - WINDOW_HEIGHT / 2 + ray->door_h / 2) * data.step;
	i = ray->dstart;
	while (i < ray->dend)
	{
		data.tex_y = (int)tex_pos & (data.texture->height - 1);
		tex_pos += data.step;
		mlx_put_pixel(cub->img, x, i++,
			((uint32_t *)data.texture->pixels)[data.tex_y
			+ data.tex_x * data.texture->width]);
	}
}
