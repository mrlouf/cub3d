/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 17:14:07 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

void	cub_print_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->rows)
	{
		j = 0;
		while (j < cub->cols)
		{
			printf("%d", cub->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	allocate_map_row(t_cub *cub, t_parser *parser, int i)
{
	cub->map[i] = malloc(sizeof(int) * parser->cols);
	if (!cub->map[i])
	{
		cub_parser_clean(parser);
		ft_exit_error(MEM_ERR, 2);
	}
}

void	cub_parser_clean(t_parser *parser)
{
	if (parser->map)
		ft_free(parser->map);
	if (parser->symbols)
		free(parser->symbols);
	if (parser->no_text)
		free(parser->no_text);
	if (parser->so_text)
		free(parser->so_text);
	if (parser->ea_text)
		free(parser->ea_text);
	if (parser->we_text)
		free(parser->we_text);
	if (parser->c_color)
		free(parser->c_color);
	if (parser->f_color)
		free(parser->f_color);
}
