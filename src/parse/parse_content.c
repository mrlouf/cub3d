/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 11:00:55 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	cub_check_content_colors(char *color)
{
	char	*copy;
	char	**tab;
	char	*trim;
	int		i;
	int		code;

	copy = ft_strtrim(color, "FC ");
	tab = ft_split(copy, ',');
	if (ft_array_count(tab) != 3)
	{
		ft_free(tab);
		return (free(copy), ft_putendl_fd(CINFO_ERR, 2), 1);
	}
	free(copy);
	i = 0;
	while (i < ft_array_count(tab))
	{
		trim = ft_strtrim(tab[i], " \n");
		code = ft_atoi(tab[i]);
		if (trim[0] == '\0' ||!ft_isdigit_str(trim) || code < 0 || code > 255)
			return (free(trim), ft_free(tab), ft_putendl_fd(CINFO_ERR, 2), 1);
		free(trim);
		i++;
	}
	return (ft_free(tab), 0);
}

int	cub_check_texture_extension(char *filename, char *extension)
{
	int			fd;
	char		*point;
	struct stat	f_stat;

	if (stat(filename, &f_stat) == -1)
	{
		if (errno == ENOENT)
			return (ft_putendl_fd(NO_TEXT_ERR, 2), 1);
		else if (errno == EACCES)
			return (ft_putendl_fd(NO_TEXT_PERM_ERR, 2), 1);
		return (ft_putendl_fd(STAT_TEXT_ERR, 2), 1);
	}
	if (S_ISDIR(f_stat.st_mode))
		return (ft_putendl_fd(PATH_DIR_ERR, 2), 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd(TEXT_OPEN_ERR, 2), 1);
	close(fd);
	point = ft_strchr(filename, '.');
	if (point && !ft_strcmp(point, extension))
		return (0);
	return (ft_putendl_fd(TEXT_EXT_ERR, 2), 1);
}

int	cub_check_content_textures(char *texture)
{
	char	*path;

	path = ft_strtrim(texture, "NSOEAW/. \n");
	if (cub_check_texture_extension(path, ".png"))
	{
		free(path);
		return (1);
	}
	if (ft_strnstr(path, "forbidden", ft_strlen(path)))
	{
		free(path);
		return (ft_putendl_fd(TEXT_FORB_ERR, 2), 1);
	}
	free(path);
	return (0);
}
