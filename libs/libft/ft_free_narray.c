/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_narray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:51:01 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 11:02:32 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Frees a double pointer array: if n < 0, it will free the whole array
	(assuming it is NULL terminated), otherwise it will free n elements.
*/
void	ft_free_narray(void **array, int n)
{
	int	i;

	i = -1;
	if (n < 0)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}
