/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 15:12:30 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

void	cub_skip_header(int fd, int *i)
{
	char	*line;

	*i = 0;
	line = get_next_line(fd);
	while (line && *i < 6)
	{
		if (line[0] != '\n')
			(*i)++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

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

int	cub_check_map_space(t_parser *parser, char **map, int i, int j)
{
	if (i > 0 && j > 0 && map[i - 1][j - 1] != '1' && map[i - 1][j - 1] != ' ')
		return (1);
	if (i > 0 && map[i - 1][j] != '1' && map[i - 1][j] != ' ')
		return (1);
	if (i > 0 && j < parser->rows - 1
		&& map[i - 1][j + 1] != '1' && map[i - 1][j + 1] != ' ')
		return (1);
	if (j > 0 && map[i][j - 1] != '1' && map[i][j - 1] != ' ')
		return (1);
	if (j < parser->rows - 1 && map[i][j + 1] != '1' && map[i][j + 1] != ' ')
		return (1);
	if (i < parser->rows - 1 && j > 0
		&& map[i + 1][j - 1] != '1' && map[i + 1][j - 1] != ' ')
		return (1);
	if (i < parser->rows - 1 && map[i + 1][j] != '1' && map[i + 1][j] != ' ')
		return (1);
	if (i < parser->rows - 1 && j < parser->cols - 1
		&& map[i + 1][j + 1] != '1' && map[i + 1][j + 1] != ' ')
		return (1);
	return (0);
}

int	cub_check_map_borders(t_parser *parser, char **map)
{
	int		i;
	char	*trim;

	i = 0;
	while (map[i] && i < parser->rows - 1)
	{
		trim = ft_strtrim(map[i], " ");
		if (trim[0] != '\0')
		{
			if (trim[0] == 'N' || trim[ft_strlen(trim) - 1] == 'N'
				|| trim[0] == 'S' || trim[ft_strlen(trim) - 1] == 'S'
				|| trim[0] == 'E' || trim[ft_strlen(trim) - 1] == 'E'
				|| trim[0] == 'W' || trim[ft_strlen(trim) - 1] == 'W')
				return (free(trim), ft_putendl_fd(MAP_PLAYER_BORDER_ERR, 2), 1);
			if (trim[0] != '1' || trim[ft_strlen(trim) - 1] != '1')
				return (free(trim), ft_putendl_fd(MAP_WALL_ERR, 2), 1);
			free(trim);
			trim = NULL;
		}
		if (trim)
			free(trim);
		i++;
	}
	return (0);
}
