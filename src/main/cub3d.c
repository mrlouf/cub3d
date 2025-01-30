/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:24:55 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 17:02:11 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	cub_cub3d(char **av)
{
	(void)av;
	/*if (cub_init())
		return (1);*/
	if (cub_parse(av[1]))
		return (1);
	/*if (cub_raycast())
		return (1);*/
	printf("GOOD MAP!!\n");
	return (0);
}
