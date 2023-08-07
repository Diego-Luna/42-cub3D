/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:13:35 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:13:38 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_save_color_in_structur(t_color *color, char *str)
{
	char	*r;
	char	*g;
	char	*b;

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

void	ft_save_color(t_state *state, char *file)
{
	int		fd;
	char	*line;
	char	*cut;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		cut = ft_cut_space(line, 0);
		if (ft_str_equals(cut, "F") == TRUE)
		{
			ft_save_color_in_structur(&state->map.f_color, ft_cut_word(line,
					' ', 2));
		}
		else if (ft_str_equals(cut, "C") == TRUE)
		{
			ft_save_color_in_structur(&state->map.c_color, ft_cut_word(line,
					' ', 2));
		}
		cut = ft_free(cut);
		line = ft_free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_save_img(t_state *state, char *file)
{
	int		fd;
	char	*line;
	char	*cut;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		cut = ft_cut_space(line, 0);
		if (ft_str_equals(cut, "NO") == TRUE)
			state->map.path_no = ft_cut_word(line, ' ', 2);
		else if (ft_str_equals(cut, "SO") == TRUE)
			state->map.path_so = ft_cut_word(line, ' ', 2);
		else if (ft_str_equals(cut, "WE") == TRUE)
			state->map.path_we = ft_cut_word(line, ' ', 2);
		else if (ft_str_equals(cut, "EA") == TRUE)
			state->map.path_ea = ft_cut_word(line, ' ', 2);
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
