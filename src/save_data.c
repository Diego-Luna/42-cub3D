/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:56:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 12:16:52 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

void save_imgs(t_state *state, char *file){
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
// void save_map(t_state *state, char *file){

// 	char	*line;

// 	line = get_next_line(file);
// 	state->height	= 0;
// 	state->width = 0;
// 	if (line == NULL)
// 		return
// 	state->width = ft_strlen(line);
// 	while (line != NULL)
// 	{
// 		line = get_next_line(file);
// 		state->height++;
// 		if (state->width < ft_strlen(line))
// 			state->width = ft_strlen(line);
// 	}
// }

void save_data(t_state *state, char *file){
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	line = get_next_line(fd);
	i++;
	while (line != NULL)
	{
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	if (i < 9){
		ft_error_print("Error in map", state);
	}
	save_imgs(state, file);
	// save_colors(state, file);
	// save_map(state, file);
}