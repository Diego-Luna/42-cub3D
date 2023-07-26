/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:11:25 by diegofranci       #+#    #+#             */
/*   Updated: 2023/07/26 13:11:31 by diegofranci      ###   ########.fr       */
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
  // for (int y = drawStart; y <= drawEnd; y++){
    // mlx_put_pixel(img, x, y, color);
  // }
}

void  ft_raycasting(t_state *state)
{
  // int x;
  uint32_t x;

  x = 0;
  if (state->ray.g_img){
    mlx_delete_image(state->game.mlx, state->ray.g_img);
  }
  state->ray.g_img = mlx_new_image(state->game.mlx, WINDOW_W, WINDOW_H);
  while (x < (int)WINDOW_W)
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
    double deltaDistX = (state->ray.rayDirX == 0) ? 1e30 : fabs(1 / state->ray.rayDirX);
    double deltaDistY = (state->ray.rayDirY == 0) ? 1e30 : fabs(1 / state->ray.rayDirY);
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
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
      // if (mapY < (int)WINDOW_H && mapX < (int)WINDOW_W)
      // {
        // if (state->map.map[mapY][mapX] > 0) hit = 1;
        if (state->map.map[mapY][mapX] == 1) hit = 1;
      // }
    }

    // //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);

    //Calculate height of line to draw on screen
    int lineHeight = (int)(WINDOW_H / perpWallDist);
    //calculate lowest and highest pixel to fill in current stripe
    // int drawStart = -lineHeight / 2 + WINDOW_H / 2;
    uint32_t drawStart = -lineHeight / 2 + WINDOW_H / 2;
    if(drawStart < 0)drawStart = 0;
    // int drawEnd = lineHeight / 2 + WINDOW_H / 2;
    uint32_t drawEnd = lineHeight / 2 + WINDOW_H / 2;
    if(drawEnd >= (int)WINDOW_H)drawEnd = WINDOW_H - 1;

    // choose wall color
    mlx_verLine(state->ray.g_img, x, drawStart, drawEnd, get_rgba(255, 255, 0, 255));
    x++;
  }
  printf("\n raycasting");
  mlx_image_to_window(state->game.mlx, state->ray.g_img, 0, 0);
}
// void  ft_raycasting(t_state *state)
// {
//   int x;

//   x = 0;
//   mlx_image_t *g_img = mlx_new_image(state->game.mlx, state->map.width, state->map.height);
//   while (x < (int)state->map.width)
//   {
//     //calculate ray position and direction
//     state->ray.cameraX = 2 * x / (double)state->map.width - 1; //x-coordinate in camera space
//     state->ray.rayDirX = state->ray.dirX + state->ray.planeX * state->ray.cameraX;
//     state->ray.rayDirY = state->ray.dirY + state->ray.planeY * state->ray.cameraX;

//     //which box of the map we're in
//     int mapX = (int)state->player.x;
//     int mapY = (int)state->player.y;

//     //length of ray from current position to next x or y-side
//     double sideDistX;
//     double sideDistY;

//     //length of ray from one x or y-side to next x or y-side
//     double deltaDistX = (state->ray.rayDirX == 0) ? 1e30 : fabs(1 / state->ray.rayDirX);
//     double deltaDistY = (state->ray.rayDirY == 0) ? 1e30 : fabs(1 / state->ray.rayDirY);
//     double perpWallDist;

//     //what direction to step in x or y-direction (either +1 or -1)
//     int stepX;
//     int stepY;
//     int hit = 0; //was there a wall hit?
//     int side; //was a NS or a EW wall hit?

//     //calculate step and initial sideDist
//     if (state->ray.rayDirX < 0)
//     {
//       stepX = -1;
//       sideDistX = (state->player.x - mapX) * deltaDistX;
//     }
//     else
//     {
//       stepX = 1;
//       sideDistX = (mapX + 1.0 - state->player.x) * deltaDistX;
//     }
//     if (state->ray.rayDirY < 0)
//     {
//       stepY = -1;
//       sideDistY = (state->player.y - mapY) * deltaDistY;
//     }
//     else
//     {
//       stepY = 1;
//       sideDistY = (mapY + 1.0 - state->player.y) * deltaDistY;
//     }

//     //perform DDA
//     while (hit == 0)
//     {
//       //jump to next map square, either in x-direction, or in y-direction
//       if (sideDistX < sideDistY)
//       {
//         sideDistX += deltaDistX;
//         mapX += stepX;
//         side = 0;
//       }
//       else
//       {
//         sideDistY += deltaDistY;
//         mapY += stepY;
//         side = 1;
//       }
//       //Check if ray has hit a wall
//       if (mapY < (int)state->map.height && mapX < (int)state->map.width)
//       {
//         if (state->map.map[mapY][mapX] > 0) hit = 1;
//       }
//     }

//     // //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
//     if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//     else          perpWallDist = (sideDistY - deltaDistY);

//     //Calculate height of line to draw on screen
//     int lineHeight = (int)(state->map.height / perpWallDist);
//     //calculate lowest and highest pixel to fill in current stripe
//     int drawStart = -lineHeight / 2 + state->map.height / 2;
//     if(drawStart < 0)drawStart = 0;
//     int drawEnd = lineHeight / 2 + state->map.height / 2;
//     if(drawEnd >= (int)state->map.height)drawEnd = state->map.height - 1;

//     // choose wall color
//     mlx_verLine(g_img, x, drawStart, drawEnd, get_rgba(255, 255, 0, 255));
//     x++;
//   }
//   mlx_image_to_window(state->game.mlx, g_img, 0, 0);
// }