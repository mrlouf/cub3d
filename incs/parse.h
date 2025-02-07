/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:36:02 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 10:07:01 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <sys/stat.h>
# include "cub3d.h"

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
# define MAP_WALL_ERR "Error: map: open wall"
# define MAP_PLAYER_BORDER_ERR "Error: map: player on wall"
# define MAP_SIZE_S_ERR "Error: map: size too small"
# define MAP_SIZE_L_ERR "Error: map: size too big"
# define MAP_DOOR_ERR "Error: map: bad door"
# define TEXT_CONV_ERR "Error: texture: failed to convert textures to images"
# define TEXT_LOAD_ERR_N "Error: texture: failed to load NORTH texture"
# define TEXT_LOAD_ERR_S "Error: texture: failed to load SOUTH texture"
# define TEXT_LOAD_ERR_E "Error: texture: failed to load EAST texture"
# define TEXT_LOAD_ERR_W "Error: texture: failed to load WEST texture"
# define TEXT_LOAD_ERR_D "Error: texture: failed to load DOOR texture"
# define TEXT_COW_ERR "Error: texture: failed to load COW texture"
# define TEXT_HORSE_ERR "Error: texture: failed to load HORSE texture"
# define TEXT_NPC1_ERR "Error: texture: failed to load NPC1 texture"
# define TEXT_P_ERR "Error: texture: failed to load PLAYER texture"
# define IMG_LOAD_ERR_N "Error: texture: failed to create NORTH image"
# define IMG_LOAD_ERR_S "Error: texture: failed to create SOUTH image"
# define IMG_LOAD_ERR_E "Error: texture: failed to create EAST image"
# define IMG_LOAD_ERR_W "Error: texture: failed to create WEST image"
# define IMG_LOAD_ERR_D "Error: texture: failed to create DOOR image"
# define IMG_P_ERR "Error: texture: failed to create PLAYER image"
# define IMG_COW_ERR "Error: texture: failed to create COW image"
# define IMG_HORSE_ERR "Error: texture: failed to create HORSE image"
# define IMG_NPC1_ERR "Error: texture: failed to create NPC1 image"

int		cub_parse(t_cub *cub, char *filename);

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
void	cub_skip_header(int fd, int *i);
void	cub_allocate_parser_map(t_parser *parser, char *filename);
int		cub_get_map_rows(char *filename);
void	cub_populate_textures(t_parser *parser, char *filename);
void	cub_populate_colors(t_parser *parser, char *filename);

//CONTENT checks
int		cub_check_content_colors(char *color);
int		cub_check_content_textures(char *texture);
int		cub_check_texture_extension(char *filename, char *extension);
int		cub_check_content_map(t_parser *parser, char **map);
int		cub_map_deep_check(t_parser *parser, char **map);
int		cub_check_map_voids(t_parser *parser, char **map);
int		cub_check_map_borders(t_parser *parser, char **map);
int		cub_check_map_space_1(t_parser *parser, char **map, int i, int j);
int		cub_check_map_space_2(t_parser *parser, char **map, int i, int j);
int		cub_check_map_player(char **map);
int		cub_check_map_symbols(t_parser *parser, char **map);
void	cub_check_map_define_symbols(t_parser *parser);
int		cub_check_doors(char **map);
int		cub_door_comprobation(int i, unsigned long j, char **map);

//TRANSFER functions
void	cub_transfer_data(t_cub *cub, t_parser *parser);
void	cub_convert_map(t_cub *cub, t_parser *parser);
void	cub_allocate_map_row(t_cub *cub, t_parser *parser, int i);
void	cub_set_player(t_cub *cub, t_parser *parser, int i, int j);
void	cub_texture_transfer(t_cub *cub, t_parser *parser);
void	cub_parser_clean(t_parser *parser);

#endif
