/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:10:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/21 19:31:36 by dluna-lo         ###   ########.fr       */
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
    t_map *map = &state->map;

    game->height = 1000;
    game->width = 1000;

    // Initialize the mlx environment
    game->mlx =  mlx_init(game->width, game->height, "CUB3D", TRUE);
    if (!game->mlx)
			ft_error_print("Error displaying the image", state);

    mlx_image_t* sky = mlx_new_image(game->mlx, game->width,  game->height  / 2);
    ft_change_full_color(sky, ft_atoi(ft_cut_word(map->c_color, ',', 1)), ft_atoi(ft_cut_word(map->c_color, ',', 2)), ft_atoi(ft_cut_word(map->c_color, ',', 3)));

		mlx_image_t* floor = mlx_new_image(game->mlx, game->width, game->height  / 2);
    ft_change_full_color(floor, ft_atoi(ft_cut_word(map->f_color, ',', 1)), ft_atoi(ft_cut_word(map->f_color, ',', 2)), ft_atoi(ft_cut_word(map->f_color, ',', 3)));

    // Draw the image to the window
    if (mlx_image_to_window(game->mlx, sky, 0, 0) == -1)
			ft_error_print("Error displaying the image", state);
    if (mlx_image_to_window(game->mlx, floor, 0, game->height / 2 ) == -1)
			ft_error_print("Error displaying the image", state);

    // Run the main loop and terminate on quit.
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
}

// run game
// 	ini 
// 	hooks
// 	crea_frams
// 	free