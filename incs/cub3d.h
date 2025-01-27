/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:23 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/27 16:01:00 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include "../libs/libft/libft.h"
# include "../libs/mlx42/include/MLX42/MLX42.h"

// DEFINES

# define WINDOW_WIDTH	320
# define WINDOW_HEIGHT	200
# define TILE_SIZE		64

// STRUCTURES

typedef struct vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
}	t_ray;

typedef struct s_cub
{
	int			**matrix;
	char		*map;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_player	*player;
	t_ray		*ray;
}	t_cub;

// PROTOTYPES

int		cub_cub3d(char **av);
int		cub_init(t_cub *cub, char **av);
int		cub_parse(t_cub *cub);
int		cub_raycast(t_cub *cub);
void	cub_clean(t_cub *cub);

#endif
