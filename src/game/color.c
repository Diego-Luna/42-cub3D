/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:14:44 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:14:45 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_change_full_color(mlx_image_t *image, int r, int g, int b)
{
	int32_t		x;
	int32_t		y;
	uint32_t	color;

	x = 0;
	while (x < (int32_t)image->width)
	{
		y = 0;
		while (y < (int32_t)image->height)
		{
			color = get_rgba(r, g, b, 255);
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_rendering(void *param)
{
	t_state	*state;

	state = param;
	ft_raycasting(state);
}
