/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:00:51 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 15:01:50 by hmunoz-g         ###   ########.fr       */
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

static void	set_texture_and_wall(t_texture_data *data, t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			data->texture = cub->w_images->we_i;
		else
			data->texture = cub->w_images->ea_i;
		data->wall_x = cub->player->pos.y + ray->wall_d * ray->dir_y;
	}
	else
	{
		if (ray->step_y > 0)
			data->texture = cub->w_images->no_i;
		else
			data->texture = cub->w_images->so_i;
		data->wall_x = cub->player->pos.x + ray->wall_d * ray->dir_x;
	}
}

static void	calculate_texture_position(t_texture_data *data, t_ray *ray)
{
	int	line_height;

	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * data->texture->width);
	if (ray->side == 0 && ray->step_x > 0)
		data->tex_x = data->texture->width - data->tex_x - 1;
	if (ray->side == 1 && ray->step_y < 0)
		data->tex_x = data->texture->width - data->tex_x - 1;
	line_height = ray->end - ray->start;
	data->step = (double)data->texture->height / line_height;
}

void	cub_update_pixels(t_cub *cub, t_ray *ray, int x)
{
	t_texture_data	data;
	double			tex_pos;
	int				i;

	set_texture_and_wall(&data, cub, ray);
	calculate_texture_position(&data, ray);
	tex_pos = (ray->start - WINDOW_HEIGHT / 2
			+ (ray->end - ray->start) / 2) * data.step;
	i = ray->start;
	while (i < ray->end)
	{
		data.tex_y = (int)tex_pos & (data.texture->height - 1);
		tex_pos += data.step;
		mlx_put_pixel(cub->img, x, i++,
			((uint32_t *)data.texture->pixels)[data.tex_y
			* data.texture->width + data.tex_x]);
	}
}
