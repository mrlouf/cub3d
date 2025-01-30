/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:23 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/30 14:07:45 by nponchon         ###   ########.fr       */
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

// TEST MAP FOR DEVELOPPING, TO BE DELETED BEFORE SUBMISSION

extern int	g_map[24][24];

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
	mlx_image_t		*img;
	mlx_texture_t	*icon;
	mlx_t			*mlx;
	t_player		*player;
}	t_cub;

// PROTOTYPES

int		cub_cub3d(char **av);
int		cub_init(t_cub *cub, char **av);
int		cub_parse(t_cub *cub, char *filename);
int		cub_start(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_hook(void *param);
int		cub_raycasting(t_cub *cub, t_ray *ray);
void	cub_clean(t_cub *cub);

#endif
