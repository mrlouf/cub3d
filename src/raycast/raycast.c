/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:41:12 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 17:47:01 by nponchon         ###   ########.fr       */
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
		if (cub->minimap_px < 10)
			cub->minimap_px++;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_KP_SUBTRACT))
		if (cub->minimap_px > 1)
			cub->minimap_px--;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_Q))
		cub->player->dir.y -= 0.1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_E))
		cub->player->dir.y += 0.1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		if (cub->player->pos.x > 1.1)
			cub->player->pos.x -= 0.1;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		if (cub->player->pos.x < 23.0)
			cub->player->pos.x += 0.1;
	}
		if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		if (cub->player->pos.y > 1.0)
			cub->player->pos.y -= 0.1;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		if (cub->player->pos.y < 23.0)
			cub->player->pos.y += 0.1;
	}
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
