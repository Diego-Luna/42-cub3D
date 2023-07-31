/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:10:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/31 18:29:27 by dluna-lo         ###   ########.fr       */
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

  game->sky = mlx_new_image(game->mlx, game->width, game->height  / 2);
	game->floor = mlx_new_image(game->mlx, game->width, game->height  / 2);
  ft_change_full_color(game->sky, map->c_color.r, map->c_color.g, map->c_color.b);
  ft_change_full_color(game->floor, map->f_color.r, map->f_color.g, map->f_color.b);
	game->tex_no = mlx_load_png(state->map.path_no);
  if (!game->tex_no)
    ft_error_print("Error in texture no", state);
	game->wall_no = mlx_texture_to_image(game->mlx, game->tex_no);
  if (!game->wall_no)
    ft_error_print("Error in img no", state);

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
  t_state *state;
  double rotSpeed = 0.1; // 0.05
  double moventSpeed = 0.1; // 0.03

  state = param;
	// printf("\n->🤖🤖🤖 left state->ray.planeX{%f} state->ray.planeY{%f}", state->ray.planeX, state->ray.planeY);
	if ((keydata.action == MLX_PRESS || state->game.key == 1) && keydata.key == MLX_KEY_W  && state->player.x + 1 < state->map.width)
  {
		state->player.x = state->player.x + (1) * state->ray.dirX * moventSpeed;
		state->player.y = state->player.y + (1) * state->ray.dirY * moventSpeed;
		state->game.key = 1;
  }
	else if (( keydata.action == MLX_PRESS || state->game.key == 2)&& keydata.key == MLX_KEY_S && state->player.x - 1 >= 0)
  {
		state->player.x = state->player.x + (-1) * state->ray.dirX * moventSpeed;
		state->player.y = state->player.y + (-1) * state->ray.dirY * moventSpeed;
		state->game.key = 2;
  }
	else if (( keydata.action == MLX_PRESS || state->game.key == 3)&& keydata.key == MLX_KEY_D && state->player.y + 1 < state->map.height)
  {
		state->player.x = state->player.x + (-1) * state->ray.dirY * moventSpeed;
		state->player.y = state->player.y - (-1) * state->ray.dirX * moventSpeed;
		state->game.key = 3;
  }
	else if (( keydata.action == MLX_PRESS || state->game.key == 4)&& keydata.key == MLX_KEY_A && state->player.y - 1 >= 0)
  {
		state->player.x = state->player.x + (1) * state->ray.dirY * moventSpeed;
		state->player.y = state->player.y - (1) * state->ray.dirX * moventSpeed;
		state->game.key = 4;
  }else if (( keydata.action == MLX_PRESS || state->game.key == 5) && keydata.key == MLX_KEY_LEFT){
    double oldDirX = state->ray.dirX;
    state->ray.dirX = state->ray.dirX * cos(-rotSpeed) - state->ray.dirY * sin(-rotSpeed);
    state->ray.dirY = oldDirX * sin(-rotSpeed) + state->ray.dirY * cos(-rotSpeed);
    double oldPlaneX = state->ray.planeX;
    state->ray.planeX = state->ray.planeX * cos(-rotSpeed) - state->ray.planeY * sin(-rotSpeed);
    state->ray.planeY = oldPlaneX * sin(-rotSpeed) + state->ray.planeY * cos(-rotSpeed);
		state->game.key = 5;
  } else if (( keydata.action == MLX_PRESS || state->game.key == 6) && keydata.key == MLX_KEY_RIGHT){
    double oldDirX = state->ray.dirX;
    state->ray.dirX = state->ray.dirX * cos(rotSpeed) - state->ray.dirY * sin(rotSpeed);
    state->ray.dirY = oldDirX * sin(rotSpeed) + state->ray.dirY * cos(rotSpeed);
    double oldPlaneX = state->ray.planeX;
    state->ray.planeX = state->ray.planeX * cos(rotSpeed) - state->ray.planeY * sin(rotSpeed);
    state->ray.planeY = oldPlaneX * sin(rotSpeed) + state->ray.planeY * cos(rotSpeed);
		state->game.key = 6;
  }else
	{
		state->game.key = 0;
	}

  ft_raycasting(state);
}

void ft_run_game(t_state *state)
{
    ft_init_game(state);
    ft_creat_frams(state);
    ft_raycasting(state);
    mlx_key_hook(state->game.mlx, &my_keyhook, state);
    // mlx_loop_hook(state->game.mlx, &ft_rendering, state);
    mlx_loop(state->game.mlx);
    ft_clone_game(state);
}

// run game
// 	ini
// 	hooks
// 	crea_frams
// 	free