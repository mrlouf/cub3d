/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:41:12 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 11:00:13 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/raycast.h"

/*
	Primary function to catch the various hooks and execute the associated
	action (eg. pressing ESC closes the window).
*/
static void	cub_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
}

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

static void	cub_draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = WINDOW_WIDTH / 3;
	while (i < WINDOW_WIDTH / 3 + MINIMAP_WIDTH)
	{
		j = MINIMAP_HEIGHT * 3;
		while (j < WINDOW_HEIGHT)
		{
			mlx_put_pixel(cub->img, i, j, 0x009900FF);
			j++;
		}
		i++;
	}
}

static void	cub_draw_image(void *param)
{
	t_cub		*cub;

	cub = param;
	cub_reset_image(cub);
	cub_draw_floor(cub);
	cub_draw_minimap(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

static int	cub_init_ray(t_cub *cub)
{
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cub->ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		cub->ray->dir_x = \
			cub->player->dir.x + cub->player->plane.x * cub->ray->camera_x;
		cub->ray->dir_y = \
			cub->player->dir.y + cub->player->plane.y * cub->ray->camera_x;
		x++;
	}
	return (0);
}

/*
	Initialises the window and the image before starting the mlx loop.
	Returns 1 if an error occured, 0 otherwise.
*/
static int	cub_init_window(t_cub *cub)
{
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	cub->img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->mlx || !cub->img)
		return (1);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_loop_hook(cub->mlx, cub_hook, cub);
	mlx_loop_hook(cub->mlx, cub_draw_image, cub);
	mlx_loop(cub->mlx);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	return (0);
}

int	cub_raycast(t_cub *cub)
{
	if (cub_init_ray(cub))
		return (1);
	if (cub_init_window(cub))
		return (1);
	return (0);
}
