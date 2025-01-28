/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:41:12 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 15:01:59 by nponchon         ###   ########.fr       */
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
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_ADD))
		while (cub->minimap_px < 10)
			cub->minimap_px++;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_SUBTRACT))
		while (cub->minimap_px > 1)
			cub->minimap_px--;
}

/*
	Initialises the window and the image before starting the mlx loop.
	Returns 1 if an error occured, 0 otherwise.
*/
static int	cub_start(t_cub *cub)
{
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	cub->img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->mlx || !cub->img)
		return (1);
	cub_draw(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_loop_hook(cub->mlx, cub_hook, cub);
	mlx_loop_hook(cub->mlx, cub_loop, cub);
	mlx_loop(cub->mlx);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	return (0);
}

/*
	The main loop used in during the execution of cub3d and repeated
	everytime the image needs to be refreshed. Updates the players position,
	then renders the image.
*/
void	cub_loop(void *param)
{
	t_cub		*cub;

	cub = param;
	cub_draw(cub);
}

int	cub_raycast(t_cub *cub)
{
	if (cub_init_pixels(cub))
		return (1);
	if (cub_start(cub))
		return (1);
	return (0);
}
