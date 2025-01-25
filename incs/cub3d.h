/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:23 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/25 12:46:39 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include "../libs/libft/libft.h"
# include "../libs/mlx42/include/MLX42/MLX42.h"

# include "./init.h"
# include "./parse.h"
# include "./raycast.h"

int	cub_cub3d(char **av);

#endif