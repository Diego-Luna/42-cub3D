/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:10:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/01 19:58:29 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int get_rgba(int r, int g, int b, int a)
{
  return (r << 24 | g << 16 | b << 8 | a);
}

void  ft_change_degree_radias(t_state *state, double radias)
{
  double oldDirX = state->ray.dirX;
  state->ray.dirX = state->ray.dirX * cos(radias) - state->ray.dirY * sin(radias);
  state->ray.dirY = oldDirX * sin(radias) + state->ray.dirY * cos(radias);
  double oldPlaneX = state->ray.planeX;
  state->ray.planeX = state->ray.planeX * cos(radias) - state->ray.planeY * sin(radias);
  state->ray.planeY = oldPlaneX * sin(radias) + state->ray.planeY * cos(radias);
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

void	ft_complete_map(char **map){
	size_t i;
	size_t ii;

	i = 0;
	while (map[i])
	{
		ii = 0;
    // printf("\n 🖥 {%s}", map[i]);
		while (map[i][ii])
		{
      if (ft_valid_info(map[i][ii]) == 0){
        map[i][ii] = 'P';
      }
			ii++;
		}
		i++;
	}
}

void ft_init_game(t_state *state)
{
  t_game *game = &state->game;

  if (state->map.direccion == 'N')
    ft_change_degree_radias(state, 4.71239);
  if (state->map.direccion == 'S')
    ft_change_degree_radias(state, 1.5708);
  if (state->map.direccion == 'W')
    ft_change_degree_radias(state, 3.14159 );
  // game->height = 1000;
  // game->width = 1000;
  game->height = HEIGHT;
  game->width = WIDTH;
  game->mlx =  mlx_init(WINDOW_W,  WINDOW_H, "CUB3D", TRUE);
  if (!game->mlx)
	ft_error_print("Error displaying the image", state);
  // ft_complete_map(state);
	// ft_print_map(state);

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
  game->img_no = mlx_texture_to_image(state->game.mlx, game->tex_no);
  if (!game->img_no)
    ft_error_print("Error in texture no", state);
	// game->tex_so = mlx_load_png(state->map.path_so);
  // if (!game->tex_so)
  //   ft_error_print("Error in texture so", state);
	// game->tex_we = mlx_load_png(state->map.path_we);
  // if (!game->tex_we)
  //   ft_error_print("Error in texture we", state);
	// game->tex_ea = mlx_load_png(state->map.path_ea);
  // if (!game->tex_ea)
  //   ft_error_print("Error in texture no", state);

  // Draw the image to the window
  mlx_resize_image(game->img_no, game->width, game->height);
  // if (mlx_image_to_window(game->mlx, game->img_no, 0, 0) == -1)
		// ft_error_print("Error displaying the image", state);
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

int ft_movent_posiblel_WS(t_state *state, int redreccion, double moventSpeed)
{
  double x;
  double y;

  x = state->player.x + (redreccion) * state->ray.dirX * moventSpeed;
	y = state->player.y + (redreccion) * state->ray.dirY * moventSpeed;

  printf("\n --> 🧘🏾‍♀️ x{%f}, y{%f}, state->map.width{%zu}, state->map.height{%zu} ", x, y, state->map.width, state->map.height);
  if (x >= (double)state->map.width - 2  || x < 1)
    return (0);
  if (y >= (double)state->map.height -1  || y < 1)
    return (0);
  if (state->map.map[(int)y][(int)x] == '1')
  {
    return (0);
  }
  return (1);
}

int ft_movent_posiblel_AD(t_state *state, int redreccion, double moventSpeed)
{
  double x;
  double y;

  x = state->player.x + (redreccion) * state->ray.dirY * moventSpeed;
  y = state->player.y - (redreccion) * state->ray.dirX * moventSpeed;

  printf("\n --> 🧘🏾 x{%f}, y{%f}, state->map.width{%zu}, state->map.height{%zu} ", x, y, state->map.width, state->map.height);
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

void my_keyhook(mlx_key_data_t keydata, void* param)
{
  t_state *state;
  double rotSpeed = 0.24; // 0.05
  double moventSpeed = 0.24; // 0.03
  state = param;

  if(keydata.key == MLX_KEY_ESCAPE)
    ft_error_print(NULL, state);

	if (((keydata.action == MLX_PRESS || state->game.key == 1)) && (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)  && state->player.x + 1 < state->map.width && ft_movent_posiblel_WS(state, 1, moventSpeed) == 1)
  {
    state->player.x = state->player.x + (1) * state->ray.dirX * moventSpeed;
    state->player.y = state->player.y + (1) * state->ray.dirY * moventSpeed;
    state->game.key = 1;
  }
  if (( keydata.action == MLX_PRESS || state->game.key == 2)&& (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && state->player.x - 1 >= 0 && ft_movent_posiblel_WS(state, -1, moventSpeed) == 1)
  {
    state->player.x = state->player.x + (-1) * state->ray.dirX * moventSpeed;
    state->player.y = state->player.y + (-1) * state->ray.dirY * moventSpeed;
    state->game.key = 2;
  }
  if (( keydata.action == MLX_PRESS || state->game.key == 3)&& keydata.key == MLX_KEY_D && state->player.y + 1 < state->map.height && ft_movent_posiblel_AD(state, -1, moventSpeed) == 1)
  {
    state->player.x = state->player.x + (-1) * state->ray.dirY * moventSpeed;
    state->player.y = state->player.y - (-1) * state->ray.dirX * moventSpeed;
    state->game.key = 3;
  }
  if (( keydata.action == MLX_PRESS || state->game.key == 4)&& keydata.key == MLX_KEY_A && state->player.y - 1 >= 0 && ft_movent_posiblel_AD(state, 1, moventSpeed) == 1)
  {
    state->player.x = state->player.x + (1) * state->ray.dirY * moventSpeed;
    state->player.y = state->player.y - (1) * state->ray.dirX * moventSpeed;
    state->game.key = 4;
  } if (( keydata.action == MLX_PRESS || state->game.key == 5) && keydata.key == MLX_KEY_LEFT){
    double oldDirX = state->ray.dirX;
    state->ray.dirX = state->ray.dirX * cos(-rotSpeed) - state->ray.dirY * sin(-rotSpeed);
    state->ray.dirY = oldDirX * sin(-rotSpeed) + state->ray.dirY * cos(-rotSpeed);
    double oldPlaneX = state->ray.planeX;
    state->ray.planeX = state->ray.planeX * cos(-rotSpeed) - state->ray.planeY * sin(-rotSpeed);
    state->ray.planeY = oldPlaneX * sin(-rotSpeed) + state->ray.planeY * cos(-rotSpeed);
    state->game.key = 5;
  }  if (( keydata.action == MLX_PRESS || state->game.key == 6) && keydata.key == MLX_KEY_RIGHT){
    double oldDirX = state->ray.dirX;
    state->ray.dirX = state->ray.dirX * cos(rotSpeed) - state->ray.dirY * sin(rotSpeed);
    state->ray.dirY = oldDirX * sin(rotSpeed) + state->ray.dirY * cos(rotSpeed);
    double oldPlaneX = state->ray.planeX;
    state->ray.planeX = state->ray.planeX * cos(rotSpeed) - state->ray.planeY * sin(rotSpeed);
    state->ray.planeY = oldPlaneX * sin(rotSpeed) + state->ray.planeY * cos(rotSpeed);
    state->game.key = 6;
  }
  ft_raycasting(state);
}

void ft_run_game(t_state *state)
{
    ft_init_game(state);
    ft_creat_frams(state);
    ft_raycasting(state);
    mlx_key_hook(state->game.mlx, &my_keyhook, state);
    mlx_loop(state->game.mlx);
    ft_clone_game(state);
}

// run game
// 	ini
// 	hooks
// 	crea_frams
// 	free