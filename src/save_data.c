/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:56:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/18 18:55:26 by dluna-lo         ###   ########.fr       */
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
	state->width = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	line = get_next_line(fd);
	i++;
	while (line != NULL)
	{
		if (i >= state->start_map && ft_is_map(line) == TRUE){
			start++;
			if (ft_strlen(line) > state->width)
				state->width = ft_strlen(line);
		}
		if (i >= state->start_map && ft_is_map(line) == FALSE){
			break;
		}
		line = ft_free(line);
		line = get_next_line(fd);
		i++;
	}
	line = ft_free(line);
	close(fd);
	state->height = start;
}

char *ft_clean_last(char *str, t_state *state)
{
	int i;
	int ii;
	char *new;

	i = 0;
	ii = 0;
	new = ft_calloc(sizeof(char), ft_strlen(str));
	if (!new)
		ft_error_print("", state);
	while (str[i])
	{
		if (str[i] != '\n'){
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
	state->map = ft_calloc(sizeof(char*), state->height + 1);
	line = get_next_line(fd);
	i++;
	while (line != NULL)
	{
		if (i >= state->start_map && ft_is_map(line) == TRUE)
			state->map[ii++] = ft_clean_last(line, state);
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

	map = state->map;
	if (c != '0')
		return ;
	if ((x == state->width - 1) || y == state->height - 1 || x == 0
		|| y == 0)
		ft_error_print("Error no Map valid 🤯", state);
	if (x != 0 && y != 0
			&& ((map[y][x - 1] && map[y][x - 1] == ' ')
			|| (map[y][x + 1] && map[y][x + 1] == ' ')
			|| ((y - 1) < state->height && x < ft_strlen(map[y - 1]) && map[y - 1][x] == ' ')
			|| ((y + 1) < state->height && x < ft_strlen(map[y + 1]) && map[y + 1][x] == ' ')
			)
		)
		ft_error_print("Error no Map valid 🤯", state);
}


void ft_map_validity(t_state *state, void (*f)(t_state *, char, size_t, size_t))
{
	size_t x;
	size_t y;

	y = 0;
	while (state->map[y])
	{
		x = 0;
		while (state->map[y][x])
		{
			(*f)(state, state->map[y][x], y, x);
			x++;
		}
		y++;
	}
}

int ft_check_map(t_state *state){
	ft_map_validity(state, ft_is_map_close);
	return (TRUE);
}
