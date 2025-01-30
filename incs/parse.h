/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:36:02 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 11:12:09 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <sys/stat.h>
# include "./cub3d.h"

//ERROR messages
# define MEM_ERR "Error: memory allocation failed"
# define N_TEXTURE_ERR "Error: wrong amount of textures"
# define N_COLOR_ERR "Error: wrong amount of colors"
# define MAP_POS_ERR "Error: map must be last"
# define NO_MAP_ERR "Error: missing map"
# define NO_FILE_ERR "Error: file does not exist"
# define NO_PERM_ERR "Error: permission denied"
# define OPEN_ERR "Error: cannot open file"
# define FORB_ERR "Error: forbidden input file"
# define EXT_ERR "Error: bad extension"
# define CINFO_ERR "Error: bad color info"
# define NO_TEXT_ERR "Error: texture: can't find texture"
# define NO_TEXT_PERM_ERR "Error: texture: permission denied"
# define STAT_TEXT_ERR "Error: texture: stat error"
# define PATH_DIR_ERR "Error: texture: path is a directory"
# define TEXT_OPEN_ERR "Error: texture: cannot open file"
# define TEXT_EXT_ERR "Error: texture: cannot open file"
# define TEXT_FORB_ERR "Error: texture: forbidden file"
# define MAP_CHAR_ERR "Error: map: bad character"
# define MAP_NO_PLAYER_ERR "Error: map: missing player"
# define MAP_N_PLAYER_ERR "Error: map: more than one player"
# define MAP_VOID_ERR "Error: map: open void"

typedef struct s_parser
{
	int		n_t[4];
	int		n_c[2];
	int		rows;
	int		cols;
	char	**map;
	char	*f_color;
	char	*c_color;
	char	*no_text;
	char	*so_text;
	char	*ea_text;
	char	*we_text;
	char	**symbols;
}	t_parser;

int		cub_parse(char *filename);

//FORMAT checks
int		cub_format_checks(t_parser *parser, char *filename);
int		cub_check_format_extension(char *filename, char *extension);
int		cub_check_format_map_position(char *filename);
int		check_line_start(char *line);
int		find_map_start(int fd, char **line);
int		cub_check_format_map_existence(char *filename);
int		cub_check_format_textures(t_parser *p, char *filename);
int		cub_check_format_colors(t_parser *parser, char *filename);

//POPULATOR functions
void	cub_populate_parser(t_parser *parser, char *filename);
void	cub_populate_map(t_parser *parser, char *filename);
void	cub_allocate_parser_map(t_parser *parser, char *filename);
int		cub_get_map_rows(char *filename);
void	cub_populate_textures(t_parser *parser, char *filename);
void	cub_populate_colors(t_parser *parser, char *filename);

//CONTENT checks
int		cub_check_content_colors(char *color);
int		cub_check_content_textures(char *texture);
int		cub_check_texture_extension(char *filename, char *extension);
int		cub_check_content_map(t_parser *parser, char **map);
int		cub_check_map_voids(t_parser *parser, char **map);
int		cub_check_map_borders(t_parser *parser, char **map);
int		cub_check_map_space(t_parser *parser, char **map, int i, int j);
int		cub_check_map_player(char **map);
int		cub_check_map_symbols(t_parser *parser, char **map);
void	cub_check_map_define_symbols(t_parser *parser);

#endif
