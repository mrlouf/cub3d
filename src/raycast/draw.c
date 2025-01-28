/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 13:20:11 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/raycast.h"

/*
	Used to reset the image before drawing the new frame by setting all
	pixels to a certain colour.
*/
static void	cub_reset_image(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		j = -1;
		while (++j < WINDOW_HEIGHT)
		{
			mlx_put_pixel(cub->img, i, j, 0x6CBBFFFF);
		}
	}
}

static void	cub_draw_minipx(t_cub *cub, int j, int i, int colour)
{
	int	ii;
	int	jj;

	ii = i + cub->minimap_px;
	jj = j + cub->minimap_px;
	while (i < ii && i < WINDOW_WIDTH)
	{
		while (j < jj && j < WINDOW_HEIGHT)
			mlx_put_pixel(cub->img, j++, i, colour);
		j -= cub->minimap_px;
		i++;
	}
}

/*
	Draws the minimap on the image after the floor, ceiling and walls
	have been rendered.
	Indicates the walls and the player's position.
	TODO
	- Add a cone of vision in front of the player
*/
static void	cub_draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 25)
	{
		j = -1;
		while (++j < 25)
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
}

/*
	Draws the floor by painting the bottom half of the screen
	in a certain colour.
*/
void	cub_draw_floor(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = WINDOW_HEIGHT / 2;
		while (j < WINDOW_HEIGHT)
		{
			mlx_put_pixel(cub->img, i, j, 0x8B4513FF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

void	cub_draw(void *param)
{
	t_cub		*cub;

	cub = param;
	cub_reset_image(cub);
	cub_draw_floor(cub);
	cub_draw_minimap(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}
