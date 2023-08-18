/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_heigth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:14:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/17 16:33:19 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_get_map_heigth_utils(t_state *state, int *start, char *line)
{
	(*start)++;
	if (ft_strlen(line) > state->map.width)
	{
		state->map.width = ft_strlen(line);
	}
}

void	ft_get_map_heigth_utils_1(char *line, int fd, int start, t_state *state)
{
	line = ft_free(line);
	close(fd);
	state->map.height = start;
}

void	ft_get_map_heigth(t_state *state, char *file)
{
	int		i;
	int		start;
	int		fd;
	char	*line;
	int	check;

	i = 0;
	start = 0;
	state->map.width = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File does not exist", state);
	line = get_next_line(fd);
	i++;
	check = TRUE;
	while (line != NULL)
	{
		if (i >= state->map.start_map && ft_is_map(line) == TRUE)
		{
			ft_get_map_heigth_utils(state, &start, line);
		}
		if (i >= state->map.start_map && ft_is_map(line) == FALSE)
			break ;
		line = ft_free(line);
		line = get_next_line(fd);
		i++;
	}
	ft_get_map_heigth_utils_1(line, fd, start, state);
}
