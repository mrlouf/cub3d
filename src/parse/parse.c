/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 09:53:21 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

void	cub_populate_parser(t_parser *parser, char *filename)
{
	int	i;

	cub_allocate_parser_map(parser, filename);
	cub_populate_map(parser, filename);
	cub_populate_textures(parser, filename);
	cub_populate_colors(parser, filename);
	parser->rows = ft_array_count(parser->map);
	i = -1;
	parser->cols = ft_strlen(parser->map[0]);
	while (++i < parser->rows)
	{
		if (ft_strlen(parser->map[i]) > (size_t)parser->cols)
			parser->cols = ft_strlen(parser->map[i]);
	}
}

int	cub_content_checks(t_parser *parser)
{
	if (cub_check_content_colors(parser->f_color))
		return (1);
	if (cub_check_content_colors(parser->c_color))
		return (1);
	if (cub_check_content_textures(parser->no_text))
		return (1);
	if (cub_check_content_textures(parser->so_text))
		return (1);
	if (cub_check_content_textures(parser->ea_text))
		return (1);
	if (cub_check_content_textures(parser->we_text))
		return (1);
	if (cub_check_content_map(parser, parser->map))
		return (1);
	return (0);
}

int	cub_format_checks(t_parser *parser, char *filename)
{
	if (cub_check_format_extension(filename, ".cub"))
		return (1);
	if (cub_check_format_map_existence(filename))
		return (1);
	if (cub_check_format_map_position(filename))
		return (1);
	if (cub_check_format_textures(parser, filename))
		return (1);
	if (cub_check_format_colors(parser, filename))
		return (1);
	return (0);
}

void	cub_init_parser(t_parser *parser, char *filename)
{
	int		i;
	int		fd;
	char	*line;

	i = -1;
	while (++i < 4)
		parser->n_t[i] = 0;
	i = -1;
	while (++i < 2)
		parser->n_c[i] = 0;
	parser->map = NULL;
	parser->symbols = NULL;
	parser->rows = 0;
	parser->cols = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		parser->rows++;
		if ((int)ft_strlen(line) > parser->cols)
			parser->cols = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	cub_parse(t_cub *cub, char *filename)
{
	t_parser	parser;
	double		ratio;

	cub_init_parser(&parser, filename);
	if (cub_format_checks(&parser, filename))
		return (1);
	ratio = WINDOW_HEIGHT / parser.rows;
	if (ratio < 9.00)
		return (ft_putendl_fd(MAP_SIZE_L_ERR, 2), 1);
	cub_populate_parser(&parser, filename);
	if (cub_content_checks(&parser))
	{
		cub_parser_clean(&parser);
		return (1);
	}
	cub_transfer_data(cub, &parser);
	return (0);
}
