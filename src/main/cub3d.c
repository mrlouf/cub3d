/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:24:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/25 12:42:53 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	cub_cub3d(char **av)
{
	(void)av;
	if (cub_init())
		return (1);
	if (cub_parse())
		return (1);
	if (cub_raycast())
		return (1);
	return (0);
}
