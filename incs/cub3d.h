/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:23 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/07 11:07:05 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <sys/time.h>

# include "../libs/libft/libft.h"
# include "../libs/libft/ft_printf/includes/ft_printf.h"
# include "../libs/mlx42/include/MLX42/MLX42.h"
# include "sprites.h"

// DEFINES

# define WINDOW_WIDTH	1440
# define WINDOW_HEIGHT	960
# define MINIMAP_WIDTH	200
# define MINIMAP_HEIGHT	100
# define MINIMAP_PX		10
# define TILE_SIZE		64
# define COOLDOWN_PERIOD 500000
# define BPP 4
# define M_PI 3.14159265358979323846

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
	mlx_texture_t			*d_t;
}	t_textures;

typedef struct s_images
{
	mlx_image_t			*no_i;
	mlx_image_t			*so_i;
	mlx_image_t			*ea_i;
	mlx_image_t			*we_i;
	mlx_image_t			*d_i;
}	t_images;

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

/*
	Ray structure for drawing walls as well as doors.
*/
typedef struct s_ray
{
	int		hit;
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
	int		door_hit;
	double	door_d;
	int		dside;
	int		door_h;
	int		dstart;
	int		dend;
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

typedef struct s_sprite
{
	t_vector	pos;
	double		distance;
	double		angle;
	int			screen_x;
	int			size;
	int			width;
	int			type;
	double		sprite_dx;
	double		sprite_dy;
	double		inv_det;	
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_size;
	int			draw_start_x;
	int			draw_end_x;
	int			x;
	int			tex_x;
}	t_sprite;

typedef struct s_zbuffer
{
	double	wall_dist;
	double	door_dist;
}	t_zbuffer;

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
	t_zbuffer		*zbuffer;
	int				door_distance;
	t_wall_txt		*w_textures;
	t_player_txt	*player_txt;
	t_cow_txt		*cow_txt;
	t_horse_txt		*horse_txt;
	t_npc_1_txt		*npc_1_txt;
	t_wall_img		*w_images;
	t_player_img	*player_img;
	t_cow_img		*cow_img;
	t_horse_img		*horse_img;
	t_npc_1_img		*npc_1_img;
	mlx_texture_t	*icon;
	mlx_t			*mlx;
	struct timeval	toggle_door;
	t_player		*player;
	mlx_image_t		*background_img;
	mlx_image_t		*raycast_img;
	mlx_image_t		*door_img;
	mlx_image_t		*obj_img_b;
	mlx_image_t		*obj_img_f;
	mlx_image_t		*mini;
	t_list			*sprites;
}	t_cub;

// PROTOTYPES

int		cub_cub3d(char **av);
int		cub_init(t_cub *cub, char **av);
void	cub_camera_init(t_cub *cub);
int		cub_parse(t_cub *cub, char *filename);
int		cub_start(t_cub *cub);
void	cub_draw(t_cub *cub);
void	cub_hook(void *param);
void	cub_clean(t_cub *cub);

#endif
