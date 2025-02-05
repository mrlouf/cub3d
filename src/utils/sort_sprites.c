/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:32:42 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/05 12:17:25 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/utils.h"

static void	cub_swap_sprites(t_list *ptr1)
{
	void	*temp;

	temp = ptr1->content;
	ptr1->content = ptr1->next->content;
	ptr1->next->content = temp;
}

static int	cub_compare_sprites(t_list *ptr1)
{
	t_sprite	*sprite1;
	t_sprite	*sprite2;

	sprite1 = (t_sprite *)ptr1->content;
	sprite2 = (t_sprite *)ptr1->next->content;
	return (sprite1->distance < sprite2->distance);
}

static void	cub_sort_iteration(t_list **sprites, t_list *lptr, int *swapped)
{
	t_list	*ptr1;

	*swapped = 0;
	ptr1 = *sprites;
	while (ptr1->next != lptr)
	{
		if (cub_compare_sprites(ptr1))
		{
			cub_swap_sprites(ptr1);
			*swapped = 1;
		}
		ptr1 = ptr1->next;
	}
}

void	cub_sort_sprites(t_list **sprites)
{
	t_list	*lptr;
	int		swapped;

	if (*sprites == NULL)
		return ;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		cub_sort_iteration(sprites, lptr, &swapped);
		lptr = ft_lstlast(lptr);
	}
}
