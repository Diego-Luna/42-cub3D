/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_frams.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:14:35 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/08 17:02:24 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_create_texture(t_state *state)
{
	t_game	*game;

	game = &state->game;
	game->tex_no = mlx_load_png(state->map.path_no);
	if (!game->tex_no)
		ft_error_print("Error in texture no", state);
	game->tex_so = mlx_load_png(state->map.path_so);
	if (!game->tex_so)
		ft_error_print("Error in texture so", state);
	game->tex_we = mlx_load_png(state->map.path_we);
	if (!game->tex_we)
		ft_error_print("Error in texture we", state);
	game->tex_ea = mlx_load_png(state->map.path_ea);
	if (!game->tex_ea)
		ft_error_print("Error in texture ea", state);
}

void	ft_create_img(t_state *state)
{
	t_game	*game;

	game = &state->game;
	game->img_no = mlx_texture_to_image(state->game.mlx, game->tex_no);
	if (!game->img_no)
		ft_error_print("Error in img no", state);
	game->img_so = mlx_texture_to_image(state->game.mlx, game->tex_so);
	if (!game->img_so)
		ft_error_print("Error in img so", state);
	game->img_we = mlx_texture_to_image(state->game.mlx, game->tex_we);
	if (!game->img_we)
		ft_error_print("Error in img we", state);
	game->img_ea = mlx_texture_to_image(state->game.mlx, game->tex_ea);
	if (!game->img_ea)
		ft_error_print("Error in img ea", state);
}

void	ft_creat_frams(t_state *state)
{
	t_game	*game;
	t_map	*map;

	game = &state->game;
	map = &state->map;
	game->sky = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H / 2);
	game->floor = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H / 2);
	ft_change_full_color(game->sky, map->c_color.r, map->c_color.g,
		map->c_color.b);
	ft_change_full_color(game->floor, map->f_color.r, map->f_color.g,
		map->f_color.b);
	ft_create_texture(state);
	ft_create_img(state);
	mlx_resize_image(game->img_no, game->width, game->height);
	mlx_resize_image(game->img_so, game->width, game->height);
	mlx_resize_image(game->img_we, game->width, game->height);
	mlx_resize_image(game->img_ea, game->width, game->height);
	if (mlx_image_to_window(game->mlx, game->sky, 0, 0) == -1)
		ft_error_print("Error displaying the image", state);
	if (mlx_image_to_window(game->mlx, game->floor, 0, WINDOW_H / 2) == -1)
		ft_error_print("Error displaying the image", state);
}
