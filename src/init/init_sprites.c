/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:37:16 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 11:01:30 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/init.h"
#include "../../incs/parse.h"

int	cub_is_sprite(char c)
{
	if (c == 'C')
		return (1);
	else if (c == 'H')
		return (2);
	else if (c == 'F')
		return (3);
	return (0);
}

void	cub_init_sprites(t_cub *cub, t_list **sprites)
{
	int			y;
	int			x;
	t_sprite	*sprite;

	*sprites = NULL;
	y = 0;
	while (y < cub->rows)
	{
		x = 0;
		while (x < cub->cols)
		{
			if (cub_is_sprite(cub->map[y][x]))
			{
				sprite = malloc(sizeof(t_sprite));
				sprite->pos.x = y + 0.5;
				sprite->pos.y = x + 0.5;
				sprite->type = cub_is_sprite(cub->map[y][x]) - 1;
				ft_lstadd_back(sprites, ft_lstnew(sprite));
			}
			x++;
		}
		y++;
	}
}
