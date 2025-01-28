/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/28 21:06:18 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/raycast.h"
#include "../../incs/utils.h"

/*
	Used to reset the image before drawing the new frame by setting all
	pixels to a certain colour.
*/
static void	cub_reset_image(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		j = -1;
		while (++j < WINDOW_HEIGHT)
		{
			mlx_put_pixel(cub->img, i, j, 0x6CBBFFFF);
		}
	}
}

/*
	Auxiliary function for the minimap, used to draw each point of the minimap
	as a block of predefined-size instead of a single pixel.
	Used to zoom in and out of the minimap.
*/
void	cub_draw_minipx(t_cub *cub, int j, int i, int colour)
{
	int	ii;
	int	jj;

	ii = i + cub->minimap_px;
	jj = j + cub->minimap_px;
	while (i < ii && i < WINDOW_WIDTH && i > 0)
	{
		while (j < jj && j < WINDOW_HEIGHT && j > 0)
			mlx_put_pixel(cub->img, j++, i, colour);
		j -= cub->minimap_px;
		i++;
	}
}

/*
	Draws the minimap on the image after the floor, ceiling and walls
	have been rendered.
	Indicates the walls and the player's position.
	TODO
	- Add a cone of vision in front of the player
*/
static void	cub_draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 25)
	{
		j = -1;
		while (++j < 25)
		{
			if (cub->map[i][j] > 0)
				cub_draw_minipx(cub, j * cub->minimap_px, \
					i * cub->minimap_px, 0x66CC00FF);
			else
				cub_draw_minipx(cub, j * cub->minimap_px, \
					i * cub->minimap_px, 0x003300FF);
		}
	}
	cub_draw_minipx(cub, cub->player->pos.y * cub->minimap_px, \
		cub->player->pos.x * cub->minimap_px, 0xFF000002);
	cub_dda(cub, cub->player->pos, cub->player->dir, 0xFF000002);
	printf("px=%f, py=%f, planex=%f, planey=%f\n", cub->player->pos.x, cub->player->pos.y, cub->player->plane.x, cub->player->plane.y);
}

/*
	Draws the floor by painting the bottom half of the screen
	in a certain colour.
*/
void	cub_draw_floor(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = WINDOW_HEIGHT / 2;
		while (j < WINDOW_HEIGHT)
		{
			mlx_put_pixel(cub->img, i, j, 0x8B4513FF);
			j++;
		}
		i++;
	}
}

static void	cub_init_ray(t_ray *ray, int x, t_player *player)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir_x = \
		player->dir.x + player->plane.x * ray->camera_x;
	ray->dir_y = \
		player->dir.y + player->plane.y * ray->camera_x;
	ray->map_x = (int)player->pos.x;
	ray->map_y = (int)player->pos.y;
	ray->delta_dx = fabs(1 / ray->dir_x);
	ray->delta_dy = fabs(1 / ray->dir_y);
	//printf("%f, %f, %f, %d, %d\n", ray->camera_x, ray->dir_x, ray->dir_y, ray->map_x, ray->map_y);
}

/*
	Calculates the step of each ray, ie. the 'direction' of the vector.
*/
static void	cub_calculate_step(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sided_x = (player->pos.x - ray->map_x) * ray->delta_dx;
	}
	else
	{
		ray->step_x = 1;
		ray->sided_x = (ray->map_x + 1.0 - player->pos.x) * ray->delta_dx;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sided_y = (player->pos.y - ray->map_y) * ray->delta_dy;
	}
	else
	{
		ray->step_y = 1;
		ray->sided_y = (ray->map_y + 1.0 - player->pos.y) * ray->delta_dy;
	}
	//printf("%d, %d, %f, %f\n", ray->step_x, ray->step_y, ray->sided_x, ray->sided_y);
}

/*
	Uses the side distances x and y from the ray to compare with the map
	to check for a potential collision with a wall.
	!A non-closed map would potentially lead to infinite calculation!
*/
static void	cub_calculate_wall_distance(t_ray *ray, int **map)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sided_x < ray->sided_y)
		{
			ray->sided_x += ray->delta_dx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sided_y += ray->delta_dy;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_x][ray->map_y] > 0)
			hit = 1;
	}
	if(ray->side == 0)
		ray->wall_d = (ray->sided_x - ray->delta_dx);
    else
		ray->wall_d = (ray->sided_y - ray->delta_dy);
	//printf("%f\n", ray->wall_d);
}

/*
	Using the distance to the wall, calculates the height (ie. the vertical size)
	of the ray to be drawn, which gives the start and end points of the ray,
	that are rounded up to zero or down to WIN_SIZE to avoid pixels out of bound.
*/
static void	cub_calculate_wall_height(t_ray *ray)
{
	ray->wall_h = (int)WINDOW_HEIGHT / ray->wall_d;
    ray->start = -ray->wall_h / 2 + WINDOW_HEIGHT / 2;
    if(ray->start < 0)
		ray->start = 0;
	ray->end = ray->wall_h / 2 + WINDOW_HEIGHT / 2;
    if(ray->end >= WINDOW_HEIGHT)
		ray->end = WINDOW_HEIGHT - 1;
	//printf("%d, %d, %d\n", ray->wall_h, ray->start, ray->end);
}

static void	cub_update_pixels(t_cub *cub, t_ray *ray, int x)
{
	int	i;
	int colour;

	i = ray->start;
	colour = 0x660000FF;
	if (ray->side != 0)
		colour = 0x330000FF;
	while (i < ray->end)
	{
		mlx_put_pixel(cub->img, x, i, colour);
		i++;
	}
}

/*
	The incredible ray-casting machinery.
	It calculates each ray needed depending on the FOV, then the step,
	wall distance and wall height of the ray before updating the pixels.
*/
static int	cub_cast_ray(t_cub *cub, t_ray *ray)
{
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cub_init_ray(ray, x, cub->player);
		cub_calculate_step(ray, cub->player);
		cub_calculate_wall_distance(ray, cub->map);
		cub_calculate_wall_height(ray);
		cub_update_pixels(cub, ray, x);
		x++;
	}
	return (0);
}

/*
	Allocates an **int matrix 'pixels', that acts as a canvas:
	each int represents a pixel in the window to be painted/drawn
	as needed for the program. Freed after the rendition,
	and allocated again for every loop of the mlx.
*/
int	cub_init_pixels(t_cub *cub)
{
	int	i;

	cub->px = malloc(sizeof(int *) * WINDOW_HEIGHT);
	if (!cub->px)
		return (1);
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		cub->px[i] = malloc(sizeof(int) * WINDOW_WIDTH);
		if (!cub->px[i])
			ft_free_narray((void **)cub->px, i);
	}
	return (0);
}

/*
	The main function for drawing all components: floor, ceiling,
	minimap and the rest. Sends the complete image to the mlx window.
*/
void	cub_draw(t_cub *cub)
{
	t_ray	ray;

	//if (cub_init_pixels(cub))
	//	return ;
	cub_reset_image(cub);
	cub_draw_floor(cub);
	cub_cast_ray(cub, &ray);
	cub_draw_minimap(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	//ft_free_narray((void **)cub->px, WINDOW_HEIGHT);
}
