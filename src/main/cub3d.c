/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:24:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/24 19:36:34 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	cub_cub3d(char **av)
{
	if (cub_init())
		return (1);
	if (cub_parse(av))
		return (1);
	if (cub_raycasting())
		return (1);
	return (0);
}
