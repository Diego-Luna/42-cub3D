/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:10:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/26 13:08:17 by diegofranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_change_full_color(mlx_image_t* image, int r, int g, int b)
{
    int32_t x;
    int32_t y;

    x = 0;
    while (x < (int32_t)image->width)
    {
        y = 0;
        while (y < (int32_t)image->height)
        {
            uint32_t color = get_rgba(r, g, b, 255);
            mlx_put_pixel(image, x, y, color);
            y++;
        }
        x++;
    }
}

void ft_init_game(t_state *state)
{
    t_game *game = &state->game;
    // t_map *map = &state->map;

    game->height = 1000;
    game->width = 1000;

    // Initialize the mlx environment
    // game->mlx =  mlx_init(game->width,  game->height, "CUB3D", TRUE);
    game->mlx =  mlx_init(WINDOW_W,  WINDOW_H, "CUB3D", TRUE);
    if (!game->mlx)
		ft_error_print("Error displaying the image", state);
}

void ft_creat_frams(t_state *state)
{
    t_game *game = &state->game;
    t_map *map = &state->map;

    // mlx_image_t* sky = mlx_new_image(game->mlx, game->width, game->height  / 2);
    game->sky = mlx_new_image(game->mlx, game->width, game->height  / 2);
    ft_change_full_color(game->sky, map->c_color.r, map->c_color.g, map->c_color.b);

	// mlx_image_t* floor = mlx_new_image(game->mlx, game->width, game->height  / 2);
	game->floor = mlx_new_image(game->mlx, game->width, game->height  / 2);
    ft_change_full_color(game->floor, map->f_color.r, map->f_color.g, map->f_color.b);

    // Draw the image to the window
    if (mlx_image_to_window(game->mlx, game->sky, 0, 0) == -1)
        ft_error_print("Error displaying the image", state);
    if (mlx_image_to_window(game->mlx, game->floor, 0, game->height / 2 ) == -1)
        ft_error_print("Error displaying the image", state);
}

void ft_clone_game(t_state *state)
{
    mlx_terminate(state->game.mlx);
}

void ft_rendering(void* param)
{
    t_state *state;

    state = param;
	// ft_raycasting(state);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
    t_state *state;

    state = param;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
    {
        if ((int)state->player.y + 1 < (int)state->map.height)
            state->player.y += 1;
        ft_raycasting(state);
    }
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
    {
        if ((int)state->player.y - 1 > 0)
            state->player.y -= 1;
        ft_raycasting(state);
    }
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
    {
        if ((int)state->player.x + 1 < (int)state->map.width)
            state->player.x += 1;
        ft_raycasting(state);
    }
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
    {
        if ((int)state->player.x - 1 > 0)
            state->player.x -= 1;
        ft_raycasting(state);
    }
}

void ft_run_game(t_state *state)
{
    ft_init_game(state);
    ft_creat_frams(state);
    // ft_raycasting(state);
    // mlx_loop_hook(state->game.mlx, &ft_rendering, state);
    mlx_key_hook(state->game.mlx, &my_keyhook, state);
    mlx_loop(state->game.mlx);
    ft_clone_game(state);
}

// run game
// 	ini
// 	hooks
// 	crea_frams
// 	free