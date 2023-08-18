/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_check_zeros.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:20:07 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/18 17:43:54 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_check_x_plus(size_t y, size_t x, char **map, int *error)
{
	if (x == 0 || (ft_strlen(map[y]) - 1) == x)
		(*error) = TRUE;
	if ((x - 1) > 0 && map[y][x - 1] == ' ')
		(*error) = TRUE;
	if ((x + 1) < (ft_strlen(map[y]) - 1) && map[y][x + 1] == ' ')
		(*error) = TRUE;
}

void	ft_is_map_check_zeros(t_state *state, char c, size_t y, size_t x)
{
	int		error;
	char	**map;

	error = FALSE;
	map = state->map.map;
	if (c == '0')
	{
		ft_check_x_plus(y, x, map, &error);
		if (y == 0 || (state->map.height - 1) == y)
			error = TRUE;
		if ((y - 1) > 0 && map[y - 1][x] == ' ')
			error = TRUE;
		if ((y - 1) > 0 && x > (ft_strlen(map[y - 1]) - 1))
			error = TRUE;
		if ((y + 1) <= (state->map.height - 1) && map[y + 1][x] == ' ')
			error = TRUE;
		if ((y + 1) <= (state->map.height - 1) && x > (ft_strlen(map[y + 1])
				- 1))
			error = TRUE;
	}
	if (error == TRUE)
		ft_error_print("map not closed", state);
}

void	ft_is_map_check_user(t_state *state, char c, size_t y, size_t x)
{
	int		error;
	char	**map;

	error = FALSE;
	map = state->map.map;
	if (c == 'W' || c == 'S' || c == 'N' || c == 'E')
	{
		if (y == 0 || (state->map.height - 1) == y)
			error = TRUE;
		if (x == 0 || (ft_strlen(map[y]) - 1) == x)
			error = TRUE;
	}
	if (error == TRUE)
		ft_error_print("invalid user position", state);
}

void	ft_is_map_check(t_state *state, char c, size_t y, size_t x)
{
	(void)y;
	(void)x;
	(void)state;
	if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W'
		&& c != 'E')
		ft_error_print("invalid character", state);
}
