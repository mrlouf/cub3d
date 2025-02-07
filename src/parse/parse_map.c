/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 10:06:33 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

void	cub_check_map_define_symbols(t_parser *parser)
{
	parser->symbols[0] = "0";
	parser->symbols[1] = "1";
	parser->symbols[2] = "N";
	parser->symbols[3] = "S";
	parser->symbols[4] = "W";
	parser->symbols[5] = "E";
	parser->symbols[6] = "C";
	parser->symbols[7] = "H";
	parser->symbols[8] = "F";
	parser->symbols[9] = " ";
	parser->symbols[10] = "\n";
	parser->symbols[11] = "2";
	parser->symbols[12] = NULL;
}

int	cub_check_map_symbols(t_parser *parser, char **map)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			k = -1;
			while (parser->symbols[++k])
				if (map[i][j] == parser->symbols[k][0])
					break ;
			if (!parser->symbols[k])
				return (ft_putendl_fd(MAP_CHAR_ERR, 2), 1);
		}
	}
	return (0);
}

int	cub_check_map_player(char **map)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				count++;
		}
	}
	if (count == 0)
		return (ft_putendl_fd(MAP_NO_PLAYER_ERR, 2), 1);
	if (count > 1)
		return (ft_putendl_fd(MAP_N_PLAYER_ERR, 2), 1);
	return (0);
}

int	cub_check_map_voids(t_parser *parser, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && j < parser->cols)
		{
			if (map[i][j] == ' ')
			{
				if (cub_check_map_space_1(parser, map, i, j))
				{
					ft_putendl_fd(MAP_VOID_ERR, 2);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	cub_check_content_map(t_parser *parser, char **map)
{
	parser->symbols = malloc(sizeof(char *) * (12 + 1));
	if (!parser->symbols)
		return (ft_putendl_fd(MEM_ERR, 2), 1);
	cub_check_map_define_symbols(parser);
	if (parser->rows < 3 || parser->cols < 3)
		return (ft_putendl_fd(MAP_SIZE_S_ERR, 2), 1);
	if (cub_map_deep_check(parser, map))
		return (1);
	return (0);
}
