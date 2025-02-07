/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 10:06:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	check_line_start(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (line[i] == '1');
}

int	find_map_start(int fd, char **line)
{
	while (*line)
	{
		if (check_line_start(*line))
			return (1);
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}

int	cub_door_comprobation(int i, unsigned long j, char **map)
{
	int	h_fail;
	int	v_fail;

	h_fail = 0;
	v_fail = 0;
	if (i > 1 && map[i - 1][j] != '1')
		v_fail = 1;
	if (i < (ft_array_count(map)) && map[i + 1][j] != '1')
		v_fail = 1;
	if (j > 1 && map[i][j - 1] != '1')
		h_fail = 1;
	if (j < (ft_strlen(map[0])) && map[i][j + 1] != '1')
		h_fail = 1;
	return (h_fail + v_fail);
}

int	cub_check_doors(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '2')
			{
				if (cub_door_comprobation(i, j, map) == 2)
					return (ft_putendl_fd(MAP_DOOR_ERR, 2), 1);
			}
		}
	}
	return (0);
}

int	cub_map_deep_check(t_parser *parser, char **map)
{
	char	**flipped;

	if (cub_check_map_symbols(parser, map))
		return (1);
	if (cub_check_doors(map))
		return (1);
	if (cub_check_map_player(map))
		return (1);
	if (cub_check_map_voids(parser, map))
		return (1);
	if (cub_check_map_borders(parser, map))
		return (1);
	flipped = ft_array_flip(map, ft_array_count(map), ft_strlen(map[0]));
	if (cub_check_map_borders(parser, flipped))
	{
		ft_free(flipped);
		return (1);
	}
	ft_free(flipped);
	return (0);
}
