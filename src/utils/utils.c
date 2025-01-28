/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 11:09:36 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

void	cub_clean(t_cub *cub)
{
	if (cub->ray)
		free(cub->ray);
	if (cub->player)
		free(cub->player);
	if (cub->filename)
		free(cub->filename);
	if (cub->map)
		ft_free_narray((void **)cub->map, WINDOW_HEIGHT);
	if (cub)
		free(cub);
}
