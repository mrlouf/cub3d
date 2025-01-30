/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:24:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 16:23:17 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

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
	/*if (cub_raycast())
		return (1);*/
	printf("GOOD MAP!!\n");
	return (0);
}
