/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:12:26 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/10 13:24:06 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

//calculate ray position and direction
//which box of the map we're in
//length of ray from one x or y-side to next x or y-side
void	ft_start_raycasting(t_state *state, int x)
{
	state->ray.camera_x = 2 * x / (double)WINDOW_W - 1;
	state->ray.ray_dir_x = state->ray.dir_x + state->ray.plane_x
		* state->ray.camera_x;
	state->ray.ray_dir_y = state->ray.dir_y + state->ray.plane_y
		* state->ray.camera_x;
	state->ray.map_x = (int)state->player.x;
	state->ray.map_y = (int)state->player.y;
	state->ray.delta_dist_x = fabs(1 / state->ray.ray_dir_x);
	state->ray.delta_dist_y = fabs(1 / state->ray.ray_dir_y);
}

//calculate step and initial sideDist
// W = -1
// E = 1
// S = -1
// N = 1
void	ft_calculate_step_and_initial(t_state *state)
{
	if (state->ray.ray_dir_x < 0)
	{
		state->ray.step_x = -1;
		state->ray.side_dist_x = (state->player.x - state->ray.map_x)
			* state->ray.delta_dist_x;
	}
	else
	{
		state->ray.step_x = 1;
		state->ray.side_dist_x = (state->ray.map_x + 1.0 - state->player.x)
			* state->ray.delta_dist_x;
	}
	if (state->ray.ray_dir_y < 0)
	{
		state->ray.step_y = -1;
		state->ray.side_dist_y = (state->player.y - state->ray.map_y)
			* state->ray.delta_dist_y;
	}
	else
	{
		state->ray.step_y = 1;
		state->ray.side_dist_y = (state->ray.map_y + 1.0 - state->player.y)
			* state->ray.delta_dist_y;
	}
}

//what direction to step in x or y-direction (either +1 or -1)
void	ft_dda(t_state *state)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (state->ray.side_dist_x < state->ray.side_dist_y)
		{
			state->ray.side_dist_x += state->ray.delta_dist_x;
			state->ray.map_x += state->ray.step_x;
			state->ray.side = SIDE_E;
			if (state->ray.step_x == -1)
				state->ray.side = SIDE_W;
		}
		else
		{
			state->ray.side_dist_y += state->ray.delta_dist_y;
			state->ray.map_y += state->ray.step_y;
			state->ray.side = SIDE_N;
			if (state->ray.step_y == -1)
				state->ray.side = SIDE_S;
		}
		if (state->map.map[state->ray.map_y][state->ray.map_x] == '1')
			hit = 1;
	}
}

//Calculate distance projected on camera direction (Euclidean distance
// would give fisheye effect!)
//Calculate height of line to draw on screen
//calculate lowest and highest pixel to fill in current stripe
void	ft_distance_camera_direction(t_state *state, int x)
{
	(void)x;
	if (state->ray.side % 2 == 0)
		state->ray.perp_wall_dist = (state->ray.side_dist_x
				- state->ray.delta_dist_x);
	else
		state->ray.perp_wall_dist = (state->ray.side_dist_y
				- state->ray.delta_dist_y);
	state->ray.line_height = (int)(WINDOW_H / state->ray.perp_wall_dist);
	state->ray.draw_start = -state->ray.line_height / 2 + WINDOW_H / 2;
	if (state->ray.draw_start < 0)
		state->ray.draw_start = 0;
	state->ray.draw_end = state->ray.line_height / 2 + WINDOW_H / 2;
	if (state->ray.draw_end >= (int)WINDOW_H)
		state->ray.draw_end = WINDOW_H - 1;
}
