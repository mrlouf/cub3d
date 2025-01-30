/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_flip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:38:22 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/29 16:23:17 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_max_cols(char **arr, int rows)
{
	int	max_cols;
	int	len;
	int	i;

	max_cols = 0;
	i = -1;
	while (++i < rows)
	{
		len = ft_strlen(arr[i]);
		if (len > max_cols)
			max_cols = len;
	}
	return (max_cols);
}

static char	get_flipped_char(char **arr, int i, int j)
{
	int	row_len;

	row_len = ft_strlen(arr[j]);
	if (i < row_len)
		return (arr[j][i]);
	return (' ');
}

char	**ft_array_flip(char **arr, int rows, int cols)
{
	char	**flipped;
	int		i;
	int		j;

	cols = get_max_cols(arr, rows);
	flipped = (char **)malloc(sizeof(char *) * (cols + 1));
	if (!flipped)
		return (NULL);
	i = -1;
	while (++i < cols)
	{
		j = -1;
		flipped[i] = ft_calloc(sizeof(char), (rows + 1));
		if (!flipped[i])
		{
			ft_free(flipped);
			return (NULL);
		}
		while (++j < rows)
			flipped[i][j] = get_flipped_char(arr, i, j);
		flipped[i][rows] = '\0';
	}
	flipped[cols] = NULL;
	return (flipped);
}
