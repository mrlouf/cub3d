/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 17:04:23 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

unsigned int	cub_convert_colors(t_cub *cub, t_parser *parser)
{
	char	**floor;
	char	**ceiling;
	char	*trimmed_f;
	char	*trimmed_c;

	trimmed_f = ft_strtrim(parser->f_color, "F ");
	trimmed_c = ft_strtrim(parser->c_color, "C ");
	floor = ft_split(trimmed_f, ',');
	ceiling = ft_split(trimmed_c, ',');
	cub->f_color = ((ft_atoi(floor[0]) & 0xFF) << 24)
		| ((ft_atoi(floor[1]) & 0xFF) << 16)
		| ((ft_atoi(floor[2]) & 0xFF) << 8) | 0xFF;
	cub->c_color = ((ft_atoi(ceiling[0]) & 0xFF) << 24)
		| ((ft_atoi(ceiling[1]) & 0xFF) << 16)
		| ((ft_atoi(ceiling[2]) & 0xFF) << 8) | 0xFF;
	ft_free(floor);
	ft_free(ceiling);
	free(trimmed_f);
	free(trimmed_c);
	return (0);
}

void	cub_set_player(t_cub *cub, t_parser *parser, int i, int j)
{
	cub->player->pos.x = i;
	cub->player->pos.y = j;
	if (parser->map[i][j] == 'N')
	{
		cub->player->dir.x = 0;
		cub->player->dir.y = 1;
	}
	else if (parser->map[i][j] == 'S')
	{
		cub->player->dir.x = 0;
		cub->player->dir.y = -1;
	}
	else if (parser->map[i][j] == 'E')
	{
		cub->player->dir.x = 1;
		cub->player->dir.y = 0;
	}
	else if (parser->map[i][j] == 'W')
	{
		cub->player->dir.x = -1;
		cub->player->dir.y = 0;
	}
	cub->map[i][j] = 0;
}

int	cub_is_valid_sym(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	cub_convert_map(t_cub *cub, t_parser *parser)
{
	int	i;
	int	j;

	cub->map = malloc(sizeof(int *) * parser->rows);
	if (!cub->map)
	{
		cub_parser_clean(parser);
		ft_exit_error(MEM_ERR, 2);
	}
	i = -1;
	while (++i < parser->rows)
	{
		allocate_map_row(cub, parser, i);
		j = -1;
		while (++j < parser->cols && parser->map[i][j])
		{
			if (ft_isspace(parser->map[i][j]))
				cub->map[i][j] = 0;
			else if (cub_is_valid_sym(parser->map[i][j]))
				cub_set_player(cub, parser, i, j);
			else
				cub->map[i][j] = parser->map[i][j] - 48;
		}
	}
}

void	cub_transfer_data(t_cub *cub, t_parser *parser)
{
	cub->rows = parser->rows;
	cub->cols = parser->cols;
	cub_convert_map(cub, parser);
	cub->no_t = ft_strdup(parser->no_text);
	cub->so_t = ft_strdup(parser->so_text);
	cub->ea_t = ft_strdup(parser->ea_text);
	cub->we_t = ft_strdup(parser->we_text);
	cub_convert_colors(cub, parser);
	cub_parser_clean(parser);
}
