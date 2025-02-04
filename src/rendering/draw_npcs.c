/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:29:11 by nponchon          #+#    #+#             */
/*   Updated: 2025/02/04 17:31:25 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/rendering.h"
#include "../../incs/utils.h"

int	cub_is_sprite(char c)
{
	if (c == 'C' || c == 'H')
		return (1);
	return (0);
}

void	cub_init_sprites(t_cub *cub, t_list **sprites)
{
	int			y;
	int			x;
	t_sprite	*sprite;

	*sprites = NULL;
	y = 0;
	while (y < cub->rows)
	{
		x = 0;
		while (x < cub->cols)
		{
			if (cub_is_sprite(cub->map[y][x]))
			{
				sprite = malloc(sizeof(t_sprite));
				sprite->pos.x = y + 0.5;
				sprite->pos.y = x + 0.5;
				sprite->type = 0;
				ft_lstadd_back(sprites, ft_lstnew(sprite));
			}
			x++;
		}
		y++;
	}
}

void	cub_update_sprite(t_cub *cub, t_sprite *sprite)
{
	double	dx;
	double	dy;
	double	sprite_dir;

	dx = sprite->pos.x - cub->player->pos.x;
	dy = sprite->pos.y - cub->player->pos.y;
	sprite->distance = sqrt(dx * dx + dy * dy);
	sprite_dir = atan2(dy, dx);
	sprite->angle = sprite_dir - cub->player->angle;
	if (sprite->angle < -M_PI)
		sprite->angle += 2 * M_PI;
	if (sprite->angle > M_PI)
		sprite->angle -= 2 * M_PI;
}

void	cub_draw_sprite_column(t_cub *cub, int x, int sprite_size, int tex_x)
{
	int		draw_start_y;
	int		draw_end_y;
	int		y;
	int		tex_y;
	uint8_t	*pixel;

	draw_start_y = (WINDOW_HEIGHT - sprite_size) / 2;
	draw_end_y = (WINDOW_HEIGHT + sprite_size) / 2;
	y = draw_start_y;
	while (y < draw_end_y)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
		{
			tex_y = (y - draw_start_y) * cub->cow_txt->height / sprite_size;
			pixel = &cub->cow_txt->pixels[(tex_y * cub->cow_txt->width + tex_x) * 4];
			if (pixel[3] > 0)
				mlx_put_pixel(cub->npc_img, x, y,
							  (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
		}
		y++;
	}
}

// Transform the sprite into camera space and draw it column-by-column.
void	cub_draw_sprite(t_cub *cub, t_sprite *sprite)
{
	double	sprite_dx;
	double	sprite_dy;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_size;
	int		draw_start_x;
	int		draw_end_x;
	int		x;
	int		tex_x;

	sprite_dx = sprite->pos.x - cub->player->pos.x;
	sprite_dy = sprite->pos.y - cub->player->pos.y;
	inv_det = 1.0 / (cub->player->plane.x * cub->player->dir.y
			- cub->player->dir.x * cub->player->plane.y);
	transform_x = inv_det * (cub->player->dir.y * sprite_dx - cub->player->dir.x * sprite_dy);
	transform_y = inv_det * (-cub->player->plane.y * sprite_dx + cub->player->plane.x * sprite_dy);
	if (transform_y <= 0)
		return ;
	sprite_screen_x = (int)((WINDOW_WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_size = abs((int)(WINDOW_HEIGHT / transform_y));
	draw_start_x = sprite_screen_x - sprite_size / 2;
	draw_end_x = sprite_screen_x + sprite_size / 2;
	for (x = draw_start_x; x < draw_end_x; x++)
	{
		if (x >= 0 && x < WINDOW_WIDTH)
		{
			if (transform_y < cub->zbuffer[x])
			{
				tex_x = (x - draw_start_x) * cub->cow_txt->width / sprite_size;
				cub_draw_sprite_column(cub, x, sprite_size, tex_x);
			}
		}
	}
}

void	cub_draw_npcs(t_cub *cub)
{
	t_list			*current;
	t_sprite		*sprite;

	cub_clear_image_fast(cub->npc_img);
	current = cub->sprites;
	while (current)
	{
		sprite = current->content;
		cub_update_sprite(cub, sprite);
		cub_draw_sprite(cub, sprite);
		current = current->next;
	}
}
