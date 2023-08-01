/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:11:25 by diegofranci       #+#    #+#             */
/*   Updated: 2023/08/01 19:38:58 by dluna-lo         ###   ########.fr       */
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
    int mapX = (int)state->player.x;
    int mapY = (int)state->player.y;

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX;
    deltaDistX = fabs(1 / state->ray.rayDirX);
    double deltaDistY;
    deltaDistY = fabs(1 / state->ray.rayDirY);
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;
    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    //calculate step and initial sideDist
    if (state->ray.rayDirX < 0)
    {
      stepX = -1;   // W
      sideDistX = (state->player.x - mapX) * deltaDistX;
    }
    else
    {
      stepX = 1;   // E
      sideDistX = (mapX + 1.0 - state->player.x) * deltaDistX;
    }
    if (state->ray.rayDirY < 0)
    {
      stepY = -1;   // S
      sideDistY = (state->player.y - mapY) * deltaDistY;
    }
    else
    {
      stepY = 1;    // N
      sideDistY = (mapY + 1.0 - state->player.y) * deltaDistY;
    }

    //perform DDA
    while (hit == 0)
    {
      //jump to next map square, either in x-direction, or in y-direction
      if (sideDistX < sideDistY)
      {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = SIDE_E; // 0 -> W and E % 2
        if (stepX == -1)
          side = SIDE_W;
      }
      else
      {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = SIDE_N; // 1 -> N and S
        if (stepY == -1)
          side = SIDE_S;
      }
      //Check if ray has hit a wall
      if (state->map.map[mapY][mapX] == '1') hit = 1;
    }
    //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if(side % 2 == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);

    //Calculate height of line to draw on screen
    int lineHeight = (int)(WINDOW_H / perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + WINDOW_H / 2;
    if(drawStart < 0)drawStart = 0;

    int drawEnd = lineHeight / 2 + WINDOW_H / 2;
    if(drawEnd >= (int)WINDOW_H)drawEnd = WINDOW_H - 1;

    mlx_verLine(state->ray.g_img, x, drawStart, drawEnd, get_rgba(255, 255, 255, 255));
    //texturing calculations
    //calculate value of wallX
    double wallX; //where exactly the wall was hit
    if (side % 2 == 0) wallX = state->player.y + perpWallDist * state->ray.rayDirY;
    else           wallX = state->player.x + perpWallDist * state->ray.rayDirX;
    wallX -= floor(wallX);
    //x coordinate on the texture
    int texX = (int)wallX * (double)state->game.tex_no->width;
    if(side % 2 == 0 && state->ray.rayDirX > 0) texX = state->game.tex_no->width - texX - 1;
    if(side % 2 != 0 && state->ray.rayDirY < 0) texX = state->game.tex_no->width - texX - 1;

    double step = 1.0 * (state->game.tex_no->height) / lineHeight;
    // Starting texture coordinate
    // double texPos = (drawStart - (WINDOW_H / 2 + lineHeight / 2)) * step;
    double texPos = (drawStart - WINDOW_H / 2 + lineHeight / 2) * step;
    for(int y = drawStart; y < drawEnd; y++)
    {
      // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
      int texY = (int)texPos & ((state->game.tex_no->height) - 1);
      texPos += step;
      uint32_t color;
      color = get_rgba(0, 0 , 255, 255);
      // if(side == SIDE_W) color = ((uint32_t *)state->game.tex_no->pixels)[x + state->game.tex_no->width * texY];
      if(side == SIDE_W) color = ((uint32_t *)state->game.tex_no->pixels)[x + state->game.tex_no->width * texY];
      // if(side == SIDE_W) color = ((uint32_t *)state->game.tex_no->pixels)[texX * texY];
      // if(side == SIDE_E) color = get_rgba(255, 255 , 255, 255);
      // if(side == SIDE_S) color = get_rgba(255, 0 , 0, 255);
      // if(side == SIDE_N) color = get_rgba(0, 0 , 255, 255);
      mlx_put_pixel(state->ray.g_img, x, y, color);
    }
    x++;
  }
  mlx_image_to_window(state->game.mlx, state->ray.g_img, 0, 0);
}
