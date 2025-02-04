/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 17:53:10 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

void	cub_draw_minipx(t_cub *cub, int j, int i, int colour);

/*
	Good old line drawing algo from FDF. It takes a start point and an
	end point as parameters and draws a line between the two points, with the
	colour as the last parameter.
*/
void	cub_dda(t_cub *cub, t_vector start, t_vector end, int colour)
{
	t_delta	delta;
	int		i;

	delta.dx = end.x - start.x;
	delta.dy = end.y - start.y;
	if (fabs(delta.dx) >= fabs(delta.dy))
		delta.step = fabs(delta.dx);
	else
		delta.step = fabs(delta.dy);
	delta.dx = delta.dx / delta.step;
	delta.dy = delta.dy / delta.step;
	delta.x = start.x;
	delta.y = start.y;
	i = 0;
	while (i++ <= delta.step)
	{
		if ((uint32_t)delta.x * cub->minimap_px < WINDOW_WIDTH
			&& (uint32_t)delta.y * cub->minimap_px < WINDOW_HEIGHT)
		{
			cub_draw_minipx(cub, delta.y * cub->minimap_px, \
		delta.x * cub->minimap_px, colour);
		}
		delta.x += delta.dx;
		delta.y += delta.dy;
	}
}

static void	cub_clean_wall_img(t_cub *cub)
{
	if (cub->w_images->no_i)
		mlx_delete_image(cub->mlx, cub->w_images->no_i);
	if (cub->w_images->so_i)
		mlx_delete_image(cub->mlx, cub->w_images->so_i);
	if (cub->w_images->ea_i)
		mlx_delete_image(cub->mlx, cub->w_images->ea_i);
	if (cub->w_images->we_i)
		mlx_delete_image(cub->mlx, cub->w_images->we_i);
	free(cub->w_images);
}

static void	cub_clean_player_img(t_cub *cub)
{
	if (cub->player_img->p_1)
		mlx_delete_image(cub->mlx, cub->player_img->p_1);
	if (cub->player_img->p_2)
		mlx_delete_image(cub->mlx, cub->player_img->p_2);
	if (cub->player_img->p_3)
		mlx_delete_image(cub->mlx, cub->player_img->p_3);
	if (cub->player_img->p_4)
		mlx_delete_image(cub->mlx, cub->player_img->p_4);
	free(cub->player_img);
}

void	cub_clean(t_cub *cub)
{
	if (!cub)
		return ;
	free(cub->player);
	free(cub->filename);
	if (cub->map)
		ft_free_narray((void **)cub->map, cub->rows);
	free(cub->no_t);
	free(cub->so_t);
	free(cub->ea_t);
	free(cub->we_t);
	if (cub->icon)
		mlx_delete_texture(cub->icon);
	if (cub->mlx)
	{
		if (cub->img)
			mlx_delete_image(cub->mlx, cub->img);
		mlx_terminate(cub->mlx);
	}
	cub_delete_wall_txt(cub);
	cub_clean_wall_img(cub);
	cub_delete_player_txt(cub);
	cub_clean_player_img(cub);
	free(cub);
}
