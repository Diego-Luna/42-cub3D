/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:56:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/18 17:30:26 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int	ft_is_map_close(t_recursive *info, int x, int y)
{
	char	old;

	if (x >= info->x_max || x < 0 || y >= info->y_max || y < 0
		|| info->map[y][x] == 0)
		return (1);
	if (info->map[y][x] == ' ')
	{
		info->map[y][x] = 'X';
		info->is_path_exit++;
		return (0);
	}
	if (info->map[y][x] == '1' || info->map[y][x] == 'X'
		|| info->map[y][x] == 0)
		return (0);
	old = info->map[y][x];
	info->map[y][x] = 'X';
	if (ft_is_map_close(info, x, y - 1) == 1 && old == '0')
		info->is_path_exit++;
	if (ft_is_map_close(info, x, y + 1) == 1 && old == '0')
		info->is_path_exit++;
	if (ft_is_map_close(info, x + 1, y) == 1 && old == '0')
		info->is_path_exit++;
	if (ft_is_map_close(info, x - 1, y) == 1 && old == '0')
		info->is_path_exit++;
	return (0);
}

void	ft_is_map_repeat(t_state *state, char c, size_t y, size_t x)
{
	if (state->map.direccion != '\0' && (c == 'N' || c == 'S' || c == 'W'
			|| c == 'E'))
		ft_error_print("Error no Map valid, repeat USER", state);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		state->map.direccion = c;
		state->player.x = (double)x;
		state->player.y = (double)y;
		if (c == 'N')
			state->player.angle = DIRECCION_NO;
		if (c == 'W')
			state->player.angle = DIRECCION_WE;
		if (c == 'S')
			state->player.angle = DIRECCION_SO;
		if (c == 'E')
			state->player.angle = DIRECCION_EA;
		ft_position_player(state, c);
	}
}

void	ft_map_validity(t_state *state, void (*f)(t_state *, char, size_t,
			size_t))
{
	size_t	x;
	size_t	y;

	y = 0;
	while (state->map.map[y])
	{
		x = 0;
		while (state->map.map[y][x])
		{
			(*f)(state, state->map.map[y][x], y, x);
			x++;
		}
		y++;
	}
}

char	**ft_duplicate_table(t_state *state, char **map, size_t heith)
{
	size_t	i;
	size_t	ii;
	char	**new;

	i = 0;
	new = ft_calloc(sizeof(char *), heith + 1);
	if (!new)
		ft_error_print("Error in malloc", state);
	while (i < heith)
	{
		new[i] = ft_calloc(state->map.width + 1, sizeof(char));
		ii = 0;
		while (map[i][ii])
		{
			new[i][ii] = map[i][ii];
			ii++;
		}
		i++;
	}
	return (new);
}

int	ft_check_map(t_state *state)
{
	t_recursive	info;
	int			i;

	ft_map_validity(state, ft_is_map_check);
	ft_map_validity(state, ft_is_map_repeat);
	ft_map_validity(state, ft_is_map_check_zeros);
	ft_map_validity(state, ft_is_map_check_user);
	if (state->map.direccion == '\0')
		ft_error_print("you need a user", state);
	info.map = ft_duplicate_table(state, state->map.map, state->map.height);
	info.is_path_exit = 0;
	info.x_max = state->map.width;
	info.y_max = state->map.height;
	ft_is_map_close(&info, state->player.x, state->player.y);
	i = 0;
	while (state->map.map[i])
	{
		if (ft_strlen(state->map.map[i]) == 0)
			ft_error_print("Map is not closed", state);
		i++;
	}
	ft_free_table(info.map);
	if (info.is_path_exit > 0)
		ft_error_print("Map is not closed", state);
	return (TRUE);
}
