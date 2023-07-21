/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:56:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/20 19:06:17 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

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

void	ft_save_map(t_state *state, char *file)
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

void	ft_save_color(t_state *state, char *file){
	int fd;
	char	*line;
	char	*cut;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		cut = ft_cut_space(line, 0);
		if (ft_str_equals(cut, "F") == TRUE){
			state->map.f_color =  ft_cut_word(line, ' ', 2);
		}
		else if (ft_str_equals(cut, "C") == TRUE){
			state->map.c_color =  ft_cut_word(line, ' ', 2);
		}
		cut = ft_free(cut);
		line = ft_free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_save_img(t_state *state, char *file)
{
	int fd;
	char	*line;
	char	*cut;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		cut = ft_cut_space(line, 0);
		if (ft_str_equals(cut, "NO") == TRUE)
			state->map.path_no =  ft_cut_word(line, ' ', 2);
		else if (ft_str_equals(cut, "SO") == TRUE)
			state->map.path_so =  ft_cut_word(line, ' ', 2);
		else if (ft_str_equals(cut, "WE") == TRUE)
			state->map.path_we =  ft_cut_word(line, ' ', 2);
		else if (ft_str_equals(cut, "EA") == TRUE)
			state->map.path_ea =  ft_cut_word(line, ' ', 2);
		cut = ft_free(cut);
		line = ft_free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_save_data(t_state *state, char *file)
{
	ft_save_map(state, file);
	ft_save_img(state, file);
	ft_save_color(state, file);
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
	if (state->map.direccion != '\0' &&  (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		ft_error_print("Error no Map valid, repeat USER 🤯", state);

	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		state->map.direccion = c;
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
	return (TRUE);
}
