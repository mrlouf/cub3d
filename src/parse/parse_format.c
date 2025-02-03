/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 17:30:42 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	cub_check_format_textures(t_parser *p, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "NO", 2))
			p->n_t[0] += 1;
		else if (!ft_strncmp(line + i, "SO", 2))
			p->n_t[1] += 1;
		else if (!ft_strncmp(line + i, "EA", 2))
			p->n_t[2] += 1;
		else if (!ft_strncmp(line + i, "WE", 2))
			p->n_t[3] += 1;
		free(line);
		line = get_next_line(fd);
	}
	if (!(p->n_t[0] == 1 && p->n_t[1] == 1 && p->n_t[2] == 1 && p->n_t[3] == 1))
		return (ft_putendl_fd(N_TEXTURE_ERR, 2), 1);
	return (0);
}

int	cub_check_format_colors(t_parser *parser, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "F", 1))
			parser->n_c[0] += 1;
		else if (!ft_strncmp(line + i, "C", 1))
			parser->n_c[1] += 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!(parser->n_c[0] == 1 && parser->n_c[1] == 1))
		return (ft_putendl_fd(N_COLOR_ERR, 2), 1);
	return (0);
}

int	cub_check_format_map_position(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!find_map_start(fd, &line))
		return (close(fd), 0);
	while (line && check_line_start(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (line[0] != '\n' && !ft_isspace(line[0]))
			return (ft_putendl_fd(MAP_POS_ERR, 2),
				free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

int	cub_check_format_map_existence(char *filename)
{
	int		fd;
	char	*line;
	int		found_map;

	fd = open(filename, O_RDONLY);
	found_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '0' || line[0] == '1')
			found_map = 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!found_map)
		return (ft_putendl_fd(NO_MAP_ERR, 2), 1);
	return (0);
}

int	cub_check_format_extension(char *filename, char *extension)
{
	int			fd;
	char		*point;
	char		*trim;

	trim = ft_strtrim(filename, "./");
	fd = open(trim, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			return (free(trim), ft_putendl_fd(NO_FILE_ERR, 2), 1);
		else if (errno == EACCES)
			return (free(trim), ft_putendl_fd(NO_PERM_ERR, 2), 1);
		return (free(trim), ft_putendl_fd(OPEN_ERR, 2), 1);
	}
	close(fd);
	if (ft_strnstr(trim, "forbidden", ft_strlen(trim)))
		return (free(trim), ft_putendl_fd(FORB_ERR, 2), 1);
	point = ft_strchr(trim, '.');
	if (point && !ft_strcmp(point, extension))
	{
		free(trim);
		return (0);
	}
	free(trim);
	return (ft_putendl_fd(EXT_ERR, 2), 1);
}
