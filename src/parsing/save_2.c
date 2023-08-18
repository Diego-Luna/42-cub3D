/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:13:48 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/18 17:13:21 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

char	*ft_clean_last(char *str, t_state *state)
{
	int		i;
	int		ii;
	char	*new;

	i = 0;
	ii = 0;
	new = ft_calloc(sizeof(char), state->map.width + 1);
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
	while (line != NULL && state->error == FALSE)
	{
		if (i >= state->map.start_map && ft_is_map(line) >= TRUE)
			state->map.map[ii++] = ft_clean_last(line, state);
		if (i >= state->map.start_map && ft_is_map(line) == FALSE)
			state->error = TRUE;
		line = ft_free(line);
		line = get_next_line(fd);
		i++;
	}
	line = ft_free(line);
	close(fd);
}
