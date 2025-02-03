/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:23 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/03 11:26:01 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>

# include "../libs/libft/libft.h"
# include "../libs/libft/ft_printf/includes/ft_printf.h"
# include "../libs/mlx42/include/MLX42/MLX42.h"

// DEFINES

# define WINDOW_WIDTH	1440
# define WINDOW_HEIGHT	960
# define MINIMAP_WIDTH	200
# define MINIMAP_HEIGHT	100
# define MINIMAP_PX		10
# define TILE_SIZE		64

// STRUCTURES

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		angle;
	double		speed;
	double		rotation;
}	t_player;

typedef struct s_textures
{
	mlx_texture_t			*no_t;
	mlx_texture_t			*so_t;
	mlx_texture_t			*ea_t;
	mlx_texture_t			*we_t;
}	t_textures;

typedef struct s_images
{
	mlx_image_t			*no_i;
	mlx_image_t			*so_i;
	mlx_image_t			*ea_i;
	mlx_image_t			*we_i;
}	t_images;

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sided_x;
	double	sided_y;
	double	delta_dx;
	double	delta_dy;
	double	wall_d;
	int		side;
	int		wall_h;
	int		start;
	int		end;
	double	wall_x;
}	t_ray;

typedef struct s_delta
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;
}	t_delta;

typedef struct s_texture_data
{
	mlx_image_t	*texture;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
}	t_texture_data;

typedef struct s_cub
{
	int				minimap_px;
	int				rows;
	int				cols;
	int				**px;
	int				**map;
	unsigned int	f_color;
	unsigned int	c_color;
	char			*filename;
	char			*no_t;
	char			*so_t;
	char			*ea_t;
	char			*we_t;
	t_textures		*w_textures;
	t_images		*w_images;
	mlx_image_t		*img;
	mlx_texture_t	*icon;
	mlx_t			*mlx;
	t_player		*player;
}	t_cub;

// PROTOTYPES

int		cub_cub3d(char **av);
int		cub_init(t_cub *cub, char **av);
void	cub_camera_init(t_cub *cub);
int		cub_parse(t_cub *cub, char *filename);
int		cub_start(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_hook(void *param);
int		cub_raycasting(t_cub *cub, t_ray *ray);
void	cub_clean(t_cub *cub);
void	cub_delete_textures(t_cub *cub);

#endif
