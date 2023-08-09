/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:13:27 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/09 12:34:09 by dluna-lo         ###   ########.fr       */
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
