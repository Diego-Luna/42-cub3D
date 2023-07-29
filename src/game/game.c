/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:10:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/29 11:37:18 by diegofranci      ###   ########.fr       */
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

void	ft_is_map_clean_space(t_state *state, char c, size_t y, size_t x)
{
	if (c == ' ')
	{
		state->map.map[y][x] = '0';
	}

}

void	ft_completa_map(t_state *state){
	size_t i;
	size_t ii;

	i = 0;
	while (i < state->map.height)
	{
		ii = ft_strlen(state->map.map[i]);
		while (ii < state->map.width)
		{
			state->map.map[i][ii] = '0';
			ii++;
		}
		i++;
	}
	ft_map_validity(state, ft_is_map_clean_space);
}

void ft_init_game(t_state *state)
{
    t_game *game = &state->game;

    game->height = 1000;
    game->width = 1000;
    game->mlx =  mlx_init(WINDOW_W,  WINDOW_H, "CUB3D", TRUE);
    if (!game->mlx)
		ft_error_print("Error displaying the image", state);
    ft_completa_map(state);
	ft_print_map(state);
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
	ft_raycasting(state);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
    // double rotSpeed = 10 * 3.0;
    t_state *state;
    double rotSpeed = 0.5;
    double movent = 0.5;

    state = param;
	printf("\n->🤖🤖🤖 left state->ray.planeX{%f} state->ray.planeY{%f}", state->ray.planeX, state->ray.planeY);

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && state->player.x + 1 < state->map.width)
  {
		if (state->ray.planeY > 0.356600 && state->ray.planeY <= 0.66 &&
        state->ray.planeX <= 0.555371 && state->ray.planeX >= -0.555371)
		{
      printf("\n -> W 1");
      state->player.x += movent;
    } else if ((state->ray.planeY >= 0.045 || state->ray.planeY <= -0.274657 || state->ray.planeY <= -0.096030 )
      && (state->ray.planeX >= 0.356600 || state->ray.planeX == 0.394992))
		{
      printf("\n -> W 2");
      state->player.y -= movent;
    }else if ((state->ray.planeY <= -0.528751 )
      && (state->ray.planeX >= 0.091))
    {
      printf("\n -> W 3");
      state->player.x -= movent;
    }else if ((state->ray.planeY < 0 || state->ray.planeY == 0.187217 || state->ray.planeY == 0.467722)
      && (state->ray.planeX < 0))
    {
      printf("\n -> W 4");
      state->player.y += movent;
    }
  }
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && state->player.x - 1 >= 0)
  {

    if (state->ray.planeY > 0.356600 && state->ray.planeY <= 0.66 &&
        state->ray.planeX <= 0.555371 && state->ray.planeX >= -0.555371)
		{
      printf("\n -> S 1");
      state->player.x -= movent;
    } else if ((state->ray.planeY >= 0.045 || state->ray.planeY <= -0.274657 || state->ray.planeY <= -0.096030 )
      && (state->ray.planeX >= 0.356600 || state->ray.planeX == 0.394992))
		{
      printf("\n -> S 2");
      state->player.y += movent;
    }else if ((state->ray.planeY <= -0.528751 )
      && (state->ray.planeX >= 0.091))
    {
      printf("\n -> S 3");
      state->player.x += movent;
    }else if ((state->ray.planeY < 0 || state->ray.planeY == 0.187217 || state->ray.planeY == 0.467722)
      && (state->ray.planeX < 0))
    {
      printf("\n -> S 4");
      state->player.y -= movent;
    }
  }
  if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && state->player.y + 1 < state->map.height)
  {
		if (state->ray.planeY > 0.356600 && state->ray.planeY <= 0.66 &&
        state->ray.planeX <= 0.555371 && state->ray.planeX >= -0.555371)
		{
      printf("\n -> D 1");
      state->player.y += movent;
    } else if ((state->ray.planeY >= 0.045 || state->ray.planeY <= -0.274657 || state->ray.planeY <= -0.096030 )
      && (state->ray.planeX >= 0.356600 || state->ray.planeX == 0.394992))
		{
      printf("\n -> D 2");
      state->player.x += movent;
    }else if ((state->ray.planeY <= -0.528751 )
      && (state->ray.planeX >= 0.091))
    {
      printf("\n -> D 3");
      state->player.y -= movent;
    }else if ((state->ray.planeY < 0 || state->ray.planeY == 0.187217 || state->ray.planeY == 0.467722)
      && (state->ray.planeX < 0))
    {
      printf("\n -> D 4");
      state->player.x -= movent;
    }
  }
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && state->player.y - 1 >= 0)
  {
		if (state->ray.planeY > 0.356600 && state->ray.planeY <= 0.66 &&
        state->ray.planeX <= 0.555371 && state->ray.planeX >= -0.555371)
		{
      printf("\n -> D 1");
      state->player.y -= movent;
    } else if ((state->ray.planeY >= 0.045 || state->ray.planeY <= -0.274657 || state->ray.planeY <= -0.096030 )
      && (state->ray.planeX >= 0.356600 || state->ray.planeX == 0.394992))
		{
      printf("\n -> D 2");
      state->player.x -= movent;
    }else if ((state->ray.planeY <= -0.528751 )
      && (state->ray.planeX >= 0.091))
    {
      printf("\n -> D 3");
      state->player.y += movent;
    }else if ((state->ray.planeY < 0 || state->ray.planeY == 0.187217 || state->ray.planeY == 0.467722)
      && (state->ray.planeX < 0))
    {
      printf("\n -> D 4");
      state->player.x += movent;
    }
  }

  if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS){
    double oldDirX = state->ray.dirX;
    state->ray.dirX = state->ray.dirX * cos(-rotSpeed) - state->ray.dirY * sin(-rotSpeed);
    state->ray.dirY = oldDirX * sin(-rotSpeed) + state->ray.dirY * cos(-rotSpeed);
    double oldPlaneX = state->ray.planeX;
    state->ray.planeX = state->ray.planeX * cos(-rotSpeed) - state->ray.planeY * sin(-rotSpeed);
    state->ray.planeY = oldPlaneX * sin(-rotSpeed) + state->ray.planeY * cos(-rotSpeed);
    // printf("\n-> 🤖 left state->ray.planeX{%f} state->ray.planeY{%f}", state->ray.planeX, state->ray.planeY);
  }
  if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS){
    double oldDirX = state->ray.dirX;
    state->ray.dirX = state->ray.dirX * cos(rotSpeed) - state->ray.dirY * sin(rotSpeed);
    state->ray.dirY = oldDirX * sin(rotSpeed) + state->ray.dirY * cos(rotSpeed);
    double oldPlaneX = state->ray.planeX;
    state->ray.planeX = state->ray.planeX * cos(rotSpeed) - state->ray.planeY * sin(rotSpeed);
    state->ray.planeY = oldPlaneX * sin(rotSpeed) + state->ray.planeY * cos(rotSpeed);
    // printf("\n-> 🤖 left state->ray.planeX{%f} state->ray.planeY{%f}", state->ray.planeX, state->ray.planeY);
  }
}

void ft_run_game(t_state *state)
{
    ft_init_game(state);
    ft_creat_frams(state);
    ft_raycasting(state);
    mlx_key_hook(state->game.mlx, &my_keyhook, state);
    mlx_loop_hook(state->game.mlx, &ft_rendering, state);
    mlx_loop(state->game.mlx);
    ft_clone_game(state);
}

// run game
// 	ini
// 	hooks
// 	crea_frams
// 	free