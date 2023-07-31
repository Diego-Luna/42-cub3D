/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:11:25 by diegofranci       #+#    #+#             */
/*   Updated: 2023/07/31 19:12:49 by dluna-lo         ###   ########.fr       */
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
  // uint32_t buffer[WINDOW_H][WINDOW_W];
  // uint32_t x;

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
    // uint32_t mapX = (uint32_t)state->player.x;
    // uint32_t mapY = (uint32_t)state->player.y;

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX;
    // if (state->ray.rayDirX == 0)
    //   deltaDistX = 1e30;
    // else
    deltaDistX = fabs(1 / state->ray.rayDirX);
    double deltaDistY;
    // if (state->ray.rayDirY == 0)
    //   deltaDistY = 1e30;
    // else
    deltaDistY = fabs(1 / state->ray.rayDirY);
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    // uint32_t stepX;
    // uint32_t stepY;
    // uint32_t hit = 0; //was there a wall hit?
    // uint32_t side; //was a NS or a EW wall hit?
    int stepX;
    int stepY;
    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    //calculate step and initial sideDist
    if (state->ray.rayDirX < 0)
    {
      stepX = -1;
      sideDistX = (state->player.x - mapX) * deltaDistX;
    }
    else
    {
      stepX = 1;
      sideDistX = (mapX + 1.0 - state->player.x) * deltaDistX;
    }
    if (state->ray.rayDirY < 0)
    {
      stepY = -1;
      sideDistY = (state->player.y - mapY) * deltaDistY;
    }
    else
    {
      stepY = 1;
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
        side = 0;
      }
      else
      {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }
      //Check if ray has hit a wall
      if (state->map.map[mapY][mapX] == '1') hit = 1;
    }

    //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);

    //Calculate height of line to draw on screen
    int lineHeight = (int)(WINDOW_H / perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe

    int drawStart = -lineHeight / 2 + WINDOW_H / 2;
    if(drawStart < 0)drawStart = 0;

    int drawEnd = lineHeight / 2 + WINDOW_H / 2;
    if(drawEnd >= (int)WINDOW_H)drawEnd = WINDOW_H - 1;

    mlx_verLine(state->ray.g_img, x, drawStart, drawEnd, get_rgba(0, 0, 0, 255));
    //texturing calculations
    // int texNum = state->map.map[mapY][mapX] - '1'; //1 subtracted from it so that texture 0 can be used!
    //calculate value of wallX
    double wallX; //where exactly the wall was hit
    if (side == 0) wallX = state->player.y + perpWallDist * state->ray.rayDirY;
    else           wallX = state->player.x + perpWallDist * state->ray.rayDirX;
    wallX -= floor(wallX);
    //x coordinate on the texture
    int texX = (int)wallX * (double)state->game.tex_no->width;
    if(side == 0 && state->ray.rayDirX > 0) texX = state->game.tex_no->width - texX - 1;
    if(side == 1 && state->ray.rayDirY < 0) texX = state->game.tex_no->width - texX - 1;

    double step = 1.0 * (state->game.tex_no->height) / lineHeight;
    // Starting texture coordinate
    double texPos = (drawStart - (WINDOW_H / 2 + lineHeight / 2)) * step;
    for(int y = drawStart; y < drawEnd; y++)
    {
      // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
      int texY = (int)texPos & ((state->game.tex_no->height) - 1);
      texPos += step;
      // uint32_t color = (uint32_t)state->game.tex_no->pixels[state->game.tex_no->height * texY + texX];

      // uint32_t  color = *(unsigned int *)(state->game.tex_no + texY
			// 	* state->game.tex_no->width + texX
			// 	* (state->game.tex_no->bytes_per_pixel / 8));
      uint32_t color = get_rgba(
          state->game.tex_no->pixels[state->game.tex_no->width * texY + texX / 8 ], state->game.tex_no->pixels[state->game.tex_no->width * texY + texX / 8 ], state->game.tex_no->pixels[state->game.tex_no->width * texY + texX / 8 ], 255);
      // uint32_t color = get_rgba(state->game.tex_no->pixels[state->game.tex_no->height * texY + texX ], state->game.tex_no->pixels[state->game.tex_no->height * texY + texX + 1], state->game.tex_no->pixels[state->game.tex_no->height * texY + texX + 2], 255);
      if(side == 1) color = get_rgba(5, 5 , 255, 255);
      mlx_put_pixel(state->ray.g_img, y, x, color);
    }
    x++;
  }

    // choose wall color
    // mlx_verLine(state->ray.g_img, x, drawStart, drawEnd, get_rgba(255, 255, 0, 255));
  mlx_image_to_window(state->game.mlx, state->ray.g_img, 0, 0);
}
