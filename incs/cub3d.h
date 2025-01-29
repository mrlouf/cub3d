/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:23 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/29 14:12:11 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>

# include "../libs/libft/libft.h"
# include "../libs/mlx42/include/MLX42/MLX42.h"

// DEFINES

# define WINDOW_WIDTH	720
# define WINDOW_HEIGHT	480
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
	int			minimap_px;
	int			**px;
	int			**map;
	char		*filename;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_player	*player;
}	t_cub;

// PROTOTYPES

int		cub_cub3d(char **av);
int		cub_init(t_cub *cub, char **av);
int		cub_parse(t_cub *cub);
int		cub_start(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_hook(void *param);
int		cub_raycasting(t_cub *cub, t_ray *ray);
void	cub_update_pixels(t_cub *cub, t_ray *ray, int x);
void	cub_clean(t_cub *cub);

#endif
