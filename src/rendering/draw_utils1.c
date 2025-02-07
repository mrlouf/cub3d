/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:00:51 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 10:41:22 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"

/*
	Allocates an **int matrix 'pixels', that acts as a canvas:
	each int represents a pixel in the window to be painted/drawn
	as needed for the program. Freed after the rendition,
	and allocated again for every loop of the mlx.
*/
int	cub_init_pixels(t_cub *cub)
{
	int	i;

	cub->px = malloc(sizeof(int *) * WINDOW_HEIGHT);
	if (!cub->px)
		return (1);
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		cub->px[i] = malloc(sizeof(int) * WINDOW_WIDTH);
		if (!cub->px[i])
			ft_free_narray((void **)cub->px, i);
	}
	return (0);
}

void	cub_set_texture_and_wall(t_texture_data *data, t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			data->texture = cub->w_images->so_i;
		else
			data->texture = cub->w_images->no_i;
		data->wall_x = cub->player->pos.y + ray->wall_d * ray->dir_y;
	}
	else
	{
		if (ray->step_y > 0)
			data->texture = cub->w_images->ea_i;
		else
			data->texture = cub->w_images->we_i;
		data->wall_x = cub->player->pos.x + ray->wall_d * ray->dir_x;
	}
}

void	cub_calculate_texture_position(t_texture_data *data, t_ray *ray)
{
	int	line_height;

	data->wall_x = fmod(data->wall_x, 1.0);
	data->tex_x = (int)(data->wall_x * data->texture->width);
	if (ray->side == 0 && ray->step_x > 0)
		data->tex_x = data->texture->width - data->tex_x - 1;
	if (ray->side == 1 && ray->step_y < 0)
		data->tex_x = data->texture->width - data->tex_x - 1;
	line_height = (int)(WINDOW_HEIGHT / ray->wall_d);
	data->step = (double)data->texture->height / line_height;
}

void	cub_update_pixels(t_cub *cub, t_ray *ray, int x)
{
	t_texture_data	data;
	double			tex_pos;
	int				i;
	uint32_t		color;
	uint8_t			*pixel_ptr;

	cub_calculate_wall_height(ray);
	cub_set_texture_and_wall(&data, cub, ray);
	cub_calculate_texture_position(&data, ray);
	tex_pos = (ray->start - WINDOW_HEIGHT / 2 + \
		(int)(WINDOW_HEIGHT / ray->wall_d) / 2) * data.step;
	i = ray->start;
	while (i < ray->end)
	{
		data.tex_y = (int)tex_pos & (data.texture->height - 1);
		tex_pos += data.step;
		pixel_ptr = &data.texture->pixels[(data.tex_y \
			* data.texture->width + data.tex_x) * BPP];
		color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
			| (pixel_ptr[2] << 8) | 0xFF;
		mlx_put_pixel(cub->raycast_img, x, i++, color);
	}
}
