/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:10:43 by diegofranci       #+#    #+#             */
/*   Updated: 2023/08/06 21:58:34 by diegofranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	my_keyhook_below(t_state *state, mlx_key_data_t keydata,
		double movent_speed)
{
	if ((keydata.action == MLX_PRESS || state->game.key == 2)
		&& (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& state->player.x - 1 >= 0 && ft_movent_posiblel_ws(state, -1,
			movent_speed) == 1)
	{
		state->player.x = state->player.x + (-1) * state->ray.dirX
			* movent_speed;
		state->player.y = state->player.y + (-1) * state->ray.dirY
			* movent_speed;
		state->game.key = 2;
	}
}

void	my_keyhook_above(t_state *state, mlx_key_data_t keydata,
		double movent_speed)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_error_print(NULL, state);
	if (((keydata.action == MLX_PRESS || state->game.key == 1))
		&& (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& state->player.x + 1 < state->map.width
		&& ft_movent_posiblel_ws(state, 1, movent_speed) == 1)
	{
		state->player.x = state->player.x + (1) * state->ray.dirX
			* movent_speed;
		state->player.y = state->player.y + (1) * state->ray.dirY
			* movent_speed;
		state->game.key = 1;
	}
}

void	my_keyhook_right(t_state *state, mlx_key_data_t keydata,
		double movent_speed)
{
	if ((keydata.action == MLX_PRESS || state->game.key == 3)
		&& keydata.key == MLX_KEY_D && state->player.y + 1 < state->map.height
		&& ft_movent_posiblel_ad(state, -1, movent_speed) == 1)
	{
		state->player.x = state->player.x + (-1) * state->ray.dirY
			* movent_speed;
		state->player.y = state->player.y - (-1) * state->ray.dirX
			* movent_speed;
		state->game.key = 3;
	}
}

void	my_keyhook_left(t_state *state, mlx_key_data_t keydata,
		double movent_speed)
{
	if ((keydata.action == MLX_PRESS || state->game.key == 4)
		&& keydata.key == MLX_KEY_A && state->player.y - 1 >= 0
		&& ft_movent_posiblel_ad(state, 1, movent_speed) == 1)
	{
		state->player.x = state->player.x + (1) * state->ray.dirY
			* movent_speed;
		state->player.y = state->player.y - (1) * state->ray.dirX
			* movent_speed;
		state->game.key = 4;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_state	*state;
	double	rot_speed;
	double	movent_speed;

	rot_speed = 0.05;
	movent_speed = 0.05;
	state = param;
	my_keyhook_above(state, keydata, movent_speed);
	my_keyhook_below(state, keydata, movent_speed);
	my_keyhook_right(state, keydata, movent_speed);
	my_keyhook_left(state, keydata, movent_speed);
	my_keyhook_rotate_right(state, keydata, rot_speed);
	my_keyhook_rotate_left(state, keydata, rot_speed);
	ft_raycasting(state);
}
