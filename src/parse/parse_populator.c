/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_populator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 09:19:59 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

void	cub_populate_colors(t_parser *parser, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "F", 1))
			parser->f_color = ft_substr(line, i, ft_strlen(line));
		if (!ft_strncmp(line + i, "C", 1))
			parser->c_color = ft_substr(line, i, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	cub_populate_textures(t_parser *parser, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "NO", 2))
			parser->no_text = ft_substr(line, i, ft_strlen(line));
		if (!ft_strncmp(line + i, "SO", 2))
			parser->so_text = ft_substr(line, i, ft_strlen(line));
		if (!ft_strncmp(line + i, "EA", 2))
			parser->ea_text = ft_substr(line, i, ft_strlen(line));
		if (!ft_strncmp(line + i, "WE", 2))
			parser->we_text = ft_substr(line, i, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	cub_get_map_rows(char *filename)
{
	int		fd;
	int		i;
	int		counter;
	int		rows;
	char	*line;

	fd = open(filename, O_RDONLY);
	counter = 6;
	rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] != '\n' && line[i] != '\0')
			counter--;
		if (counter < 0 && line[i] != '\n')
			rows++;
		free(line);
		line = get_next_line(fd);
	}
	return (rows);
}

void	cub_allocate_parser_map(t_parser *parser, char *filename)
{
	parser->map = malloc(sizeof(char *) * (cub_get_map_rows(filename) + 1));
	if (!parser->map)
		ft_exit_error(MEM_ERR, 1);
}

void	cub_populate_map(t_parser *parser, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	cub_skip_header(fd, &i);
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			parser->map[++i] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	parser->map[i + 1] = NULL;
	close(fd);
}
