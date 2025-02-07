/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:24:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 10:53:34 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/hooks.h"
#include "../../incs/rendering.h"

/*
	The main loop used in during the execution of cub3d and repeated
	everytime the image needs to be refreshed. Updates the players position,
	then renders the image.
*/
void	cub_loop(void *param)
{
	t_cub		*cub;

	cub = param;
	if (!cub)
		return ;
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
	if (!cub || !cub->mlx)
		return ;
	if (xpos < WINDOW_WIDTH / 2)
	{
		cub_rotate_left(cub, 0.25);
		mlx_set_mouse_pos(cub->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	if (xpos > WINDOW_WIDTH / 2)
	{
		cub_rotate_right(cub, 0.25);
		mlx_set_mouse_pos(cub->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
}

/*
	Initialises the window and the image before starting the mlx loop.
	Returns 1 if an error occured, 0 otherwise.
*/
int	cub_start(t_cub *cub)
{
	if (cub_prep_wall_textures(cub) || cub_prep_player_textures(cub)
		|| cub_prep_cow_textures(cub) || cub_prep_horse_textures(cub)
		|| cub_prep_npc1_textures(cub))
		return (cub_clean(cub), 1);
	cub_draw_player(cub);
	mlx_set_icon(cub->mlx, cub->icon);
	cub_set_mouse(cub);
	cub_init_sprites(cub, &cub->sprites);
	cub_draw(cub);
	mlx_image_to_window(cub->mlx, cub->mini, 0, 0);
	mlx_loop_hook(cub->mlx, cub_loop, cub);
	mlx_cursor_hook(cub->mlx, cub_mouse_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}

int	cub_cub3d(char **av)
{
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
		return (1);
	if (cub_init(cub, av))
		return (cub_clean(cub), 1);
	if (cub_parse(cub, av[1]))
		return (cub_clean(cub), 1);
	if (cub_start(cub))
		return (cub_clean(cub), 1);
	return (cub_clean(cub), 0);
}
