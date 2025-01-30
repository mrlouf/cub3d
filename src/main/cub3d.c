/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:24:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 16:53:05 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/hooks.h"

/*
	The main loop used in during the execution of cub3d and repeated
	everytime the image needs to be refreshed. Updates the players position,
	then renders the image.
*/
void	cub_loop(void *param)
{
	t_cub		*cub;

	cub = param;
	cub_hook(cub);
	cub_draw(cub);
}

void	cub_set_mouse(t_cub *cub)
{
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void	cub_mouse_hook(double xpos, double ypos, void *data)
{
	t_cub	*cub;

	cub = data;
	(void)ypos;
	if (xpos < WINDOW_WIDTH / 2)
	{
		cub_rotate_left(cub);
		mlx_set_mouse_pos(cub->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	if (xpos > WINDOW_WIDTH / 2)
	{
		cub_rotate_right(cub);
		mlx_set_mouse_pos(cub->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
}

/*
	Initialises the window and the image before starting the mlx loop.
	Returns 1 if an error occured, 0 otherwise.
*/
int	cub_start(t_cub *cub)
{
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	cub->img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->mlx || !cub->img)
		return (1);
	mlx_set_icon(cub->mlx, cub->icon);
	cub_set_mouse(cub);
	cub_draw(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_loop_hook(cub->mlx, cub_loop, cub);
	mlx_cursor_hook(cub->mlx, cub_mouse_hook, cub);
	mlx_loop(cub->mlx);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_delete_texture(cub->icon);
	mlx_terminate(cub->mlx);
	return (0);
}

int	cub_cub3d(char **av)
{
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (1);
	if (cub_init(cub, av))
		return (1);
	if (cub_parse(cub, av[1]))
		return (1);
	if (cub_start(cub))
		return (1);
	cub_clean(cub);
	return (0);
}
