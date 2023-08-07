/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:10:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/06 21:48:11 by diegofranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_change_degree_radias(t_state *state, double radias)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = state->ray.dirX;
	state->ray.dirX = state->ray.dirX * cos(radias) - state->ray.dirY
		* sin(radias);
	state->ray.dirY = old_dir_x * sin(radias) + state->ray.dirY * cos(radias);
	old_plane_x = state->ray.planeX;
	state->ray.planeX = state->ray.planeX * cos(radias) - state->ray.planeY
		* sin(radias);
	state->ray.planeY = old_plane_x * sin(radias) + state->ray.planeY
		* cos(radias);
}

void	ft_init_game(t_state *state)
{
	t_game	*game;

	game = &state->game;
	if (state->map.direccion == 'N')
		ft_change_degree_radias(state, 4.71239);
	if (state->map.direccion == 'S')
		ft_change_degree_radias(state, 1.5708);
	if (state->map.direccion == 'W')
		ft_change_degree_radias(state, 3.14159);
	game->height = HEIGHT;
	game->width = WIDTH;
	game->mlx = mlx_init(WINDOW_W, WINDOW_H, "CUB3D", TRUE);
	if (!game->mlx)
		ft_error_print("Error in MLX", state);
}

int	ft_movent_posiblel_ws(t_state *state, int redreccion, double movent_speed)
{
	double	x;
	double	y;

	x = state->player.x + (redreccion) * state->ray.dirX * movent_speed;
	y = state->player.y + (redreccion) * state->ray.dirY * movent_speed;
	if (x >= (double)state->map.width - 2 || x < 1)
		return (0);
	if (y >= (double)state->map.height - 1 || y < 1)
		return (0);
	if (state->map.map[(int)y][(int)x] == '1')
	{
		return (0);
	}
	return (1);
}

int	ft_movent_posiblel_ad(t_state *state, int redreccion, double movent_speed)
{
	double	x;
	double	y;

	x = state->player.x + (redreccion) * state->ray.dirY * movent_speed;
	y = state->player.y - (redreccion) * state->ray.dirX * movent_speed;
	if (x >= (double)state->map.width - 2 || x < 1)
		return (0);
	if (y >= (double)state->map.height - 1 || y < 1)
		return (0);
	if (state->map.map[(int)y][(int)x] == '1')
	{
		return (0);
	}
	return (1);
}

void	ft_run_game(t_state *state)
{
	ft_init_game(state);
	ft_creat_frams(state);
	ft_raycasting(state);
	mlx_key_hook(state->game.mlx, &my_keyhook, state);
	mlx_loop(state->game.mlx);
	mlx_terminate(state->game.mlx);
}

// run game
// 	ini
// 	hooks
// 	crea_frams
// 	free