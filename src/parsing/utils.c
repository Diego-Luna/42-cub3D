/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:13:27 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/18 17:44:19 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int	ft_valid_info(char c)
{
	if (c == '0' || c == '1' || c == 'W' || c == 'E' || c == 'S' || c == 'N')
	{
		return (1);
	}
	return (0);
}

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

void	ft_position_player(t_state *state, char c)
{
	if (c == 'N')
	{
		state->player.x += 0.5;
		state->player.y += 0.5;
	}
	if (c == 'W')
	{
		state->player.y += 0.5;
		state->player.x += 0.5;
	}
	if (c == 'S')
	{
		state->player.x += 0.5;
		state->player.y += 0.5;
	}
	if (c == 'E')
	{
		state->player.y += 0.5;
		state->player.x += 0.5;
	}
}

size_t	ft_is_map(char *str)
{
	size_t	i;
	int		found_valid_char;

	i = 0;
	found_valid_char = FALSE;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (i == 0 || i == ft_strlen(str) - 1 || found_valid_char == FALSE)
				return (found_valid_char);
			return (TRUE);
		}
		if (str[i] == ' ' || str[i] == '1' || str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			found_valid_char++;
		i++;
	}
	return (TRUE);
}
