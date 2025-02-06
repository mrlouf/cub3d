/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_pad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:26:56 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/02/06 18:37:39 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_pad(const char *src, size_t size)
{
	char	*dst;
	size_t	src_len;
	size_t	copy_len;

	dst = ft_calloc(size + 1, sizeof(char));
	if (!dst)
		return (NULL);
	src_len = ft_strlen(src);
	if (src_len < size)
		copy_len = src_len;
	else
		copy_len = size;
	ft_memcpy(dst, src, copy_len);
	return (dst);
}
