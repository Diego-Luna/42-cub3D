/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:14:24 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:22:57 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_is_map_clean_space(t_state *state, char c, size_t y, size_t x)
{
	if (c == ' ')
	{
		state->map.map[y][x] = '0';
	}
}

void	ft_complete_map(char **map)
{
	size_t	i;
	size_t	ii;

	i = 0;
	while (map[i])
	{
		ii = 0;
		while (map[i][ii])
		{
			if (ft_valid_info(map[i][ii]) == 0)
			{
				map[i][ii] = 'P';
			}
			ii++;
		}
		i++;
	}
}

void	my_keyhook_rotate_right(t_state *state, mlx_key_data_t keydata,
		double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if ((keydata.action == MLX_PRESS || state->game.key == 5)
		&& keydata.key == MLX_KEY_LEFT)
	{
		old_dir_x = state->ray.dir_x;
		state->ray.dir_x = state->ray.dir_x * cos(-rot_speed) - state->ray.dir_y
			* sin(-rot_speed);
		state->ray.dir_y = old_dir_x * sin(-rot_speed) + state->ray.dir_y
			* cos(-rot_speed);
		old_plane_x = state->ray.plane_x;
		state->ray.plane_x = state->ray.plane_x * cos(-rot_speed)
			- state->ray.plane_y * sin(-rot_speed);
		state->ray.plane_y = old_plane_x * sin(-rot_speed) + state->ray.plane_y
			* cos(-rot_speed);
		state->game.key = 5;
	}
}

void	my_keyhook_rotate_left(t_state *state, mlx_key_data_t keydata,
		double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if ((keydata.action == MLX_PRESS || state->game.key == 6)
		&& keydata.key == MLX_KEY_RIGHT)
	{
		old_dir_x = state->ray.dir_x;
		state->ray.dir_x = state->ray.dir_x * cos(rot_speed) - state->ray.dir_y
			* sin(rot_speed);
		state->ray.dir_y = old_dir_x * sin(rot_speed) + state->ray.dir_y
			* cos(rot_speed);
		old_plane_x = state->ray.plane_x;
		state->ray.plane_x = state->ray.plane_x * cos(rot_speed)
			- state->ray.plane_y * sin(rot_speed);
		state->ray.plane_y = old_plane_x * sin(rot_speed) + state->ray.plane_y
			* cos(rot_speed);
		state->game.key = 6;
	}
}
