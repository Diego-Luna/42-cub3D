/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:11:25 by diegofranci       #+#    #+#             */
/*   Updated: 2023/08/07 11:58:04 by diegofranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void mlx_verLine(mlx_image_t *img, uint32_t x, uint32_t drawStart, uint32_t drawEnd, uint32_t color)
{
  uint32_t y;

  y = drawStart;
  while (y <= drawEnd)
  {
    mlx_put_pixel(img, x, y, color);
    y++;
  }
}

void  ft_raycasting(t_state *state)
{
  int x;

  x = 0;
  if (state->ray.g_img){
    mlx_delete_image(state->game.mlx, state->ray.g_img);
  }
  state->ray.g_img = mlx_new_image(state->game.mlx, WINDOW_W, WINDOW_H);
  while (x < WINDOW_W)
  {
    //calculate ray position and direction
    state->ray.cameraX = 2 * x / (double)WINDOW_W - 1; //x-coordinate in camera space
    state->ray.rayDirX = state->ray.dirX + state->ray.planeX * state->ray.cameraX;
    state->ray.rayDirY = state->ray.dirY + state->ray.planeY * state->ray.cameraX;

    //which box of the map we're in
    state->ray.mapX = (int)state->player.x;
    state->ray.mapY = (int)state->player.y;

    //length of ray from current position to next x or y-side
    // double sideDistX;
    // double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    // double deltaDistX;
    state->ray.deltaDistX = fabs(1 / state->ray.rayDirX);
    // double deltaDistY;
    state->ray.deltaDistY = fabs(1 / state->ray.rayDirY);
    // double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    // int stepX;
    // int stepY;
    int hit = 0; //was there a wall hit?
    // int side; //was a NS or a EW wall hit?

    //calculate step and initial sideDist
    if (state->ray.rayDirX < 0)
    {
      state->ray.stepX = -1;   // W
      state->ray.sideDistX = (state->player.x - state->ray.mapX) * state->ray.deltaDistX;
    }
    else
    {
      state->ray.stepX = 1;   // E
      state->ray.sideDistX = (state->ray.mapX + 1.0 - state->player.x) * state->ray.deltaDistX;
    }
    if (state->ray.rayDirY < 0)
    {
      state->ray.stepY = -1;   // S
      state->ray.sideDistY = (state->player.y - state->ray.mapY) * state->ray.deltaDistY;
    }
    else
    {
      state->ray.stepY = 1;    // N
      state->ray.sideDistY = (state->ray.mapY + 1.0 - state->player.y) * state->ray.deltaDistY;
    }

    //perform DDA
    while (hit == 0)
    {
      //jump to next map square, either in x-direction, or in y-direction
      if (state->ray.sideDistX < state->ray.sideDistY)
      {
        state->ray.sideDistX += state->ray.deltaDistX;
        state->ray.mapX += state->ray.stepX;
        state->ray.side = SIDE_E; // 0 -> W and E % 2
        if (state->ray.stepX == -1)
          state->ray.side = SIDE_W;
      }
      else
      {
        state->ray.sideDistY += state->ray.deltaDistY;
        state->ray.mapY += state->ray.stepY;
        state->ray.side = SIDE_N; // 1 -> N and S
        if (state->ray.stepY == -1)
          state->ray.side = SIDE_S;
      }
      //Check if ray has hit a wall
      if (state->map.map[state->ray.mapY][state->ray.mapX] == '1') hit = 1;
    }
    //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if(state->ray.side % 2 == 0) state->ray.perpWallDist = (state->ray.sideDistX - state->ray.deltaDistX);
    else          state->ray.perpWallDist = (state->ray.sideDistY - state->ray.deltaDistY);

    //Calculate height of line to draw on screen
    state->ray.lineHeight = (int)(WINDOW_H / state->ray.perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe
    state->ray.drawStart = -state->ray.lineHeight / 2 + WINDOW_H / 2;
    if(state->ray.drawStart < 0)state->ray.drawStart = 0;

    state->ray.drawEnd = state->ray.lineHeight / 2 + WINDOW_H / 2;
    if(state->ray.drawEnd >= (int)WINDOW_H)state->ray.drawEnd = WINDOW_H - 1;

    mlx_verLine(state->ray.g_img, x, state->ray.drawStart, state->ray.drawEnd, get_rgba(255, 255, 255, 255));

    double cellSizeX = WINDOW_W / (double)state->map.width;
    double cellSizeY = WINDOW_H / (double)state->map.height;
    state->ray.cellSize = fmin(cellSizeX, cellSizeY);
    mlx_resize_image(state->game.img_no, state->ray.cellSize, state->game.height);
    mlx_resize_image(state->game.img_so, state->ray.cellSize, state->game.height);
    mlx_resize_image(state->game.img_we, state->ray.cellSize, state->game.height);
    mlx_resize_image(state->game.img_ea, state->ray.cellSize, state->game.height);
    //texturing calculations
    //calculate value of wallX
    // state->ray.wallX; //where exactly the wall was hit
    if (state->ray.side % 2 == 0) state->ray.wallX = state->player.y + state->ray.perpWallDist * state->ray.rayDirY;
    else           state->ray.wallX = state->player.x + state->ray.perpWallDist * state->ray.rayDirX;
    state->ray.wallX -= floor(state->ray.wallX);

    //x coordinate on the texture
    // int texX = (int)wallX * (double)state->game.img_no->height;
    state->ray.texX = (int)(state->ray.wallX * state->ray.cellSize);

    if(state->ray.side % 2 == 0 && state->ray.rayDirX > 0) state->ray.texX = state->game.img_no->height - state->ray.texX - 1;
    if(state->ray.side % 2 != 0 && state->ray.rayDirY < 0) state->ray.texX = state->game.img_no->height - state->ray.texX - 1;

    double step = 1.0 * (state->game.img_no->height) / state->ray.lineHeight;
    // Starting texture coordinate
    double texPos = (state->ray.drawStart - WINDOW_H / 2 + state->ray.lineHeight / 2) * step;
    for(int y = state->ray.drawStart; y < state->ray.drawEnd; y++)
    {
      // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
      state->ray.texY = (int)texPos & ((state->game.img_no->height) - 1);
      texPos += step;
      uint32_t color;
      if(state->ray.side == SIDE_W) color = ((uint32_t *)state->game.img_we->pixels)[state->ray.texX + state->ray.texY * state->game.img_we->width];
      if(state->ray.side == SIDE_E) color = ((uint32_t *)state->game.img_ea->pixels)[state->ray.texX + state->ray.texY * state->game.img_ea->width];
      if(state->ray.side == SIDE_S) color = ((uint32_t *)state->game.img_so->pixels)[state->ray.texX + state->ray.texY * state->game.img_so->width];
      if(state->ray.side == SIDE_N) color = ((uint32_t *)state->game.img_no->pixels)[state->ray.texX + state->ray.texY * state->game.img_no->width];
      color = get_rgba(((color >> 16) & 0xFF), ((color >> 8) & 0xFF), (color & 0xFF), 255);
      mlx_put_pixel(state->ray.g_img, x, y, color);
    }
    x++;
  }
  mlx_image_to_window(state->game.mlx, state->ray.g_img, 0, 0);
}
