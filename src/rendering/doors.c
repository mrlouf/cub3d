/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:31:52 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 10:41:18 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"

void	cub_calculate_door_texture(t_texture_data *data, t_ray *ray)
{
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * data->texture->width);
	data->step = (double)data->texture->height \
		/ (int)(WINDOW_HEIGHT / ray->door_d);
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
	if (ray->door_d < 0.01)
		ray->door_d = 0.01;
}

void	cub_set_texture_door(t_texture_data *data, t_cub *cub, t_ray *ray)
{
	data->texture = cub->w_images->door;
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
	uint32_t		color;
	uint8_t			*pixel_ptr;

	cub_set_texture_door(&data, cub, ray);
	cub_calculate_door_texture(&data, ray);
	tex_pos = (ray->dstart - WINDOW_HEIGHT / 2 + (int)(WINDOW_HEIGHT / \
	ray->door_h) / 2) * data.step + (data.texture->height / 2);
	i = ray->dstart;
	while (i < ray->dend)
	{
		data.tex_y = (int)tex_pos & (data.texture->height - 1);
		tex_pos += data.step;
		pixel_ptr = &data.texture->pixels[(data.tex_y
				* data.texture->width + data.tex_x) * BPP];
		if (pixel_ptr[3] > 0)
		{
			color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
				| (pixel_ptr[2] << 8) | pixel_ptr[3];
			mlx_put_pixel(cub->door_img, x, i, color);
		}
		i++;
	}
}
