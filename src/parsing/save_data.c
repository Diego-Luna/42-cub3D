/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:56:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/01 18:46:57 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"
#include <string.h>

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
	new = ft_calloc(sizeof(char), state->map.width + 1);
	// new = ft_calloc(sizeof(char), ft_strlen(str));
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

void	ft_save_color_in_structur(t_color *color, char *str){
	char *r;
	char *g;
	char *b;

	r = ft_cut_word(str, ',', 1);
	g = ft_cut_word(str, ',', 2);
	b = ft_cut_word(str, ',', 3);
	color->r = ft_atoi(r);
	color->g = ft_atoi(g);
	color->b = ft_atoi(b);
	color->a = 255;
	color->s_color = str;
	ft_free(r);
	ft_free(g);
	ft_free(b);
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
			// state->map.f_color =  ft_cut_word(line, ' ', 2);
			ft_save_color_in_structur(&state->map.f_color, ft_cut_word(line, ' ', 2));
		}
		else if (ft_str_equals(cut, "C") == TRUE){
			// state->map.c_color =  ft_cut_word(line, ' ', 2);
			ft_save_color_in_structur(&state->map.c_color, ft_cut_word(line, ' ', 2));
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

int	ft_valid_info(char c)
{
	if (c == '0' || c == '1' || c == 'W' || c == 'E' || c == 'S' || c == 'N')
	{
		return (1);
	}
	return (0);
}

void	ft_is_map_close(t_recursive	*info, int x, int y)
{
	if (x >= info->x_max || x == 0 || y >= info->y_max || y < 0)
	{
		info->is_path_exit++;
		return;
	}
	if (info->map[y][x] == ' ')
	{
		info->map[y][x] = 'X';
		info->is_path_exit++;
		return ;
	}
	if (info->map[y][x] == '1' || 	info->map[y][x] == 'X')
	{
		return;
	}
	info->map[y][x] = 'X';
	ft_is_map_close(info, x, y - 1);
	ft_is_map_close(info, x, y + 1);
	ft_is_map_close(info, x + 1, y);
	ft_is_map_close(info, x - 1, y);
}

void	ft_is_map_repeat(t_state *state, char c, size_t y, size_t x)
{
	(void)c;
	if (state->map.direccion != '\0' &&  (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		ft_error_print("Error no Map valid, repeat USER 🤯", state);

	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		state->map.direccion = c;
		state->player.x = (double)x;
		state->player.y = (double)y;
		printf("\n Diego -> save x{%zu} y{%zu} maxX{%zu} maxY{%zu}", x, y, state->map.width, state->map.height);
		if (c == 'N')
			state->player.angle = DIRECCION_NO;
		if (c == 'W')
			state->player.angle = DIRECCION_WE;
		if (c == 'S')
			state->player.angle = DIRECCION_SO;
		if (c == 'E')
			state->player.angle = DIRECCION_EA;
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

char **ft_duplicate_table(t_state *state, char **map, size_t heith)
{
	size_t i;
	char **new;

	i = 0;
	new = ft_calloc(sizeof(char *), heith + 1);
	if (!new)
		ft_error_print("Error in malloc", state);
	while (i < heith)
	{
		new[i] = ft_strdup(map[i]);
		i++;
	}
	return new;
}

int	ft_check_map(t_state *state)
{
	t_recursive	info;

	ft_map_validity(state, ft_is_map_repeat);
	ft_print_map(state);
	info.map = ft_duplicate_table(state, state->map.map, state->map.height);
	// ft_complete_map(info.map);
	info.is_path_exit = 0;
	info.x_max = state->map.width;
	info.y_max = state->map.height;
	ft_is_map_close(&info, state->player.x,  state->player.y);
	ft_free_table(info.map);
	if (info.is_path_exit > 0)
		ft_error_print("Error in map no close", state);
	return (TRUE);
}
