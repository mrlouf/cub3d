/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 16:27:13 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

/*
	Auxiliary function for the minimap, used to draw each point of the minimap
	as a block of predefined-size instead of a single pixel.
	Used to zoom in and out of the minimap.
*/
void	cub_draw_minipx(t_cub *cub, int j, int i, int colour)
{
	int	ii;
	int	jj;

	ii = i + cub->minimap_px;
	jj = j + cub->minimap_px;
	while (i < ii && i < WINDOW_WIDTH && i >= 0)
	{
		while (j < jj && j < WINDOW_HEIGHT && j >= 0)
			mlx_put_pixel(cub->img, j++, i, colour);
		j -= cub->minimap_px;
		i++;
	}
}

/*
	Creates two vectors based on the player's position and direction and draws
	them using the line drawing algorithm to represent the FOV on the minimap.
*/
void	cub_draw_fov(t_cub *cub)
{
	t_vector	leftcone;
	t_vector	rightcone;

	leftcone.x = cub->player->pos.x + cos(cub->player->angle + 0.58) * 5;
	leftcone.y = cub->player->pos.y + sin(cub->player->angle + 0.58) * 5;
	rightcone.x = cub->player->pos.x + cos(cub->player->angle - 0.58) * 5;
	rightcone.y = cub->player->pos.y + sin(cub->player->angle - 0.58) * 5;
	cub_dda(cub, cub->player->pos, leftcone, 0xFF000001);
	cub_dda(cub, cub->player->pos, rightcone, 0xFF000001);
}

/*
	Draws the minimap on the image after the floor, ceiling and walls
	have been rendered.
	Indicates the walls and the player's position along with his FOV.
*/
static void	cub_draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->rows)
	{
		j = -1;
		while (++j < cub->cols)
		{
			if (cub->map[i][j] > 0)
				cub_draw_minipx(cub, j * cub->minimap_px, \
					i * cub->minimap_px, 0x66CC00FF);
			else
				cub_draw_minipx(cub, j * cub->minimap_px, \
					i * cub->minimap_px, 0x003300FF);
		}
	}
	cub_draw_minipx(cub, cub->player->pos.y * cub->minimap_px, \
		cub->player->pos.x * cub->minimap_px, 0xFF000002);
	cub_draw_fov(cub);
}

/*
	Draws the ceiling then the floor by painting each half of the screen
	in a certain colour.
*/
void	cub_draw_background(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		j = -1;
		while (++j < WINDOW_HEIGHT / 2)
			mlx_put_pixel(cub->img, i, j, cub->c_color);
	}
	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		j = WINDOW_HEIGHT / 2 - 1;
		while (++j < WINDOW_HEIGHT)
			mlx_put_pixel(cub->img, i, j, cub->f_color);
	}
}

/*
	The main function for drawing all components: floor, ceiling,
	minimap and the rest. Sends the complete image to the mlx window.
*/
void	cub_draw(t_cub *cub)
{
	t_ray	ray;

	cub_draw_background(cub);
	cub_raycasting(cub, &ray);
	cub_draw_minimap(cub);
}
