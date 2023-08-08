/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:13:12 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/08 12:58:17 by diegofranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_start_textura(t_state *state)
{
	double	cell_size_x;
	double	cell_size_y;

	cell_size_x = WINDOW_W / 1;
	cell_size_y = WINDOW_H / 1;
	state->ray.cell_size = fmin(cell_size_x, cell_size_y);
	if (state->ray.side == SIDE_N)
		mlx_resize_image(state->game.img_no, state->ray.cell_size,
			state->game.height);
	if (state->ray.side == SIDE_S)
		mlx_resize_image(state->game.img_so, state->ray.cell_size,
			state->game.height);
	if (state->ray.side == SIDE_W)
		mlx_resize_image(state->game.img_we, state->ray.cell_size,
			state->game.height);
	if (state->ray.side == SIDE_E)
		mlx_resize_image(state->game.img_ea, state->ray.cell_size,
			state->game.height);
	if (state->ray.side % 2 == 0)
		state->ray.wall_x = state->player.y + state->ray.perp_wall_dist
			* state->ray.ray_dir_y;
	else
		state->ray.wall_x = state->player.x + state->ray.perp_wall_dist
			* state->ray.ray_dir_x;
}

void	ft_textura_calculation(t_state *state)
{
	state->ray.wall_x -= floor(state->ray.wall_x);
	state->ray.tex_x = (int)(state->ray.wall_x * state->ray.cell_size);
	if (state->ray.side % 2 == 0 && state->ray.ray_dir_x > 0)
		state->ray.tex_x = state->game.img_no->height - state->ray.tex_x - 1;
	if (state->ray.side % 2 != 0 && state->ray.ray_dir_y < 0)
		state->ray.tex_x = state->game.img_no->height - state->ray.tex_x - 1;
}

uint32_t	ft_select_texture(t_state *state)
{
	if (state->ray.side == SIDE_W)
		return (((uint32_t *)state->game.img_we->pixels)[state->ray.tex_x
			+ state->ray.tex_y * state->game.img_we->width]);
	if (state->ray.side == SIDE_E)
		return (((uint32_t *)state->game.img_ea->pixels)[state->ray.tex_x
			+ state->ray.tex_y * state->game.img_ea->width]);
	if (state->ray.side == SIDE_S)
		return (((uint32_t *)state->game.img_so->pixels)[state->ray.tex_x
			+ state->ray.tex_y * state->game.img_so->width]);
	if (state->ray.side == SIDE_N)
		return (((uint32_t *)state->game.img_no->pixels)[state->ray.tex_x
			+ state->ray.tex_y * state->game.img_no->width]);
	return (get_rgba(255, 255, 255, 255));
}

//texturing calculations
// Starting texture coordinate
// Cast the texture coordinate to integer, and mask with (texHeight
// - 1) in case of overflow
void	ft_place_texture(t_state *state, int x)
{
	int			y;
	double		step;
	double		tex_pos;
	uint32_t	color;

	y = state->ray.draw_start;
	step = 1.0 * (state->game.img_no->height) / state->ray.line_height;
	tex_pos = (state->ray.draw_start - WINDOW_H / 2
			+ state->ray.line_height / 2) * step;
	while (y < state->ray.draw_end)
	{
		state->ray.tex_y = (int)tex_pos & ((state->game.img_no->height) - 1);
		tex_pos += step;
		color = ft_select_texture(state);
		color = get_rgba(((color >> 16) & 0xFF), ((color >> 8) & 0xFF),
				(color & 0xFF), 255);
		mlx_put_pixel(state->ray.g_img, x, y, color);
		y++;
	}
}

void	ft_raycasting(t_state *state)
{
	int	x;

	x = 0;
	if (state->ray.g_img)
	{
		mlx_delete_image(state->game.mlx, state->ray.g_img);
	}
	state->ray.g_img = mlx_new_image(state->game.mlx, WINDOW_W, WINDOW_H);
	while (x < WINDOW_W)
	{
		ft_start_raycasting(state, x);
		ft_calculate_step_and_initial(state);
		ft_dda(state);
		ft_distance_camera_direction(state, x);
		ft_start_textura(state);
		ft_textura_calculation(state);
		ft_place_texture(state, x);
		x++;
	}
	mlx_image_to_window(state->game.mlx, state->ray.g_img, 0, 0);
}
