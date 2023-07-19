/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:56:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/19 17:35:47 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

void	save_imgs(t_state *state, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_free(line);
		line = get_next_line(fd);
	}
	close(fd);
	(void)state;
}

void	ft_get_map_heigth(t_state *state, char *file)
{
	int		i;
	int		start;
	int		fd;
	char	*line;

	i = 0;
	start = 0;
	state->map.width = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	line = get_next_line(fd);
	i++;
	while (line != NULL)
	{
		if (i >= state->map.start_map && ft_is_map(line) == TRUE)
		{
			start++;
			if (ft_strlen(line) > state->map.width)
				state->map.width = ft_strlen(line);
		}
		if (i >= state->map.start_map && ft_is_map(line) == FALSE)
		{
			break ;
		}
		line = ft_free(line);
		line = get_next_line(fd);
		i++;
	}
	line = ft_free(line);
	close(fd);
	state->map.height = start;
}

char	*ft_clean_last(char *str, t_state *state)
{
	int		i;
	int		ii;
	char	*new;

	i = 0;
	ii = 0;
	new = ft_calloc(sizeof(char), ft_strlen(str));
	if (!new)
		ft_error_print("error in malloc", state);
	while (str[i])
	{
		if (str[i] != '\n')
		{
			new[ii] = str[i];
			ii++;
		}
		i++;
	}
	return (new);
}

void	ft_save_data(t_state *state, char *file)
{
	int		i;
	int		ii;
	int		fd;
	char	*line;

	i = 0;
	ii = 0;
	ft_get_map_heigth(state, file);
	fd = open(file, O_RDONLY);
	state->map.map = ft_calloc(sizeof(char *), state->map.height + 1);
	line = get_next_line(fd);
	i++;
	while (line != NULL)
	{
		if (i >= state->map.start_map && ft_is_map(line) == TRUE)
			state->map.map[ii++] = ft_clean_last(line, state);
		line = ft_free(line);
		line = get_next_line(fd);
		i++;
	}
	line = ft_free(line);
	close(fd);
}

void	ft_is_map_close(t_state *state, char c, size_t y, size_t x)
{
	char	**map;

	map = state->map.map;
	if (c != '0')
		return ;
	if ((x == ft_strlen(map[y]) - 1) || y == state->map.height - 1 || x == 0
		|| y == 0)
		ft_error_print("Error no Map valid, not close 🤯", state);
	if (x != 0 && y != 0 && ((map[y][x - 1] && map[y][x - 1] == ' ')
			|| (map[y][x + 1] && map[y][x + 1] == ' ') || ((y
					- 1) < state->map.height && x < ft_strlen(map[y - 1])
				&& map[y - 1][x] == ' ') || ((y + 1) < state->map.height
				&& x < ft_strlen(map[y + 1]) && map[y + 1][x] == ' ')))
		ft_error_print("Error no Map valid, not close 🤯", state);
}

void	ft_is_map_repeat(t_state *state, char c, size_t y, size_t x)
{
	(void)x;
	(void)y;
	(void)c;
	if (c == 'N')
		state->map.n_no++;
	if (c == 'S')
		state->map.n_so++;
	if (c == 'W')
		state->map.n_we++;
	if (c == 'E')
		state->map.n_ea++;
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

int	ft_check_map(t_state *state)
{
	state->map.n_no = 0;
	state->map.n_so = 0;
	state->map.n_we = 0;
	state->map.n_ea = 0;
	ft_map_validity(state, ft_is_map_close);
	ft_map_validity(state, ft_is_map_repeat);
	if (state->map.n_ea > 1 || state->map.n_so > 1 || state->map.n_we > 1
		|| state->map.n_no > 1)
		ft_error_print("Error no Map valid, repeat USER 🤯", state);
	if (state->map.n_ea == 0 && state->map.n_so == 0 && state->map.n_we == 0
		&& state->map.n_no == 0)
		ft_error_print("Error no Map valid, repeat USER 🤯", state);

	if (state->map.n_ea == 1 && (state->map.n_so != 0 || state->map.n_we != 0 || state->map.n_no != 0))
		ft_error_print("Error no Map valid, repeat USER 🤯", state);
	if (state->map.n_so == 1 && ( state->map.n_ea != 0 || state->map.n_we != 0 || state->map.n_no != 0))
		ft_error_print("Error no Map valid, repeat USER 🤯", state);
	if (state->map.n_we == 1 && (state->map.n_no != 0 || state->map.n_ea != 0 || state->map.n_so != 0  ))
		ft_error_print("Error no Map valid, repeat USER 🤯", state);
	if ( state->map.n_no == 1 && (state->map.n_ea != 0 || state->map.n_so != 0 || state->map.n_we != 0))
		ft_error_print("Error no Map valid, repeat USER 🤯", state);
	return (TRUE);
}
