/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:47:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/05 18:46:39 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

int ft_check_file(char *file, t_state *state){

	int		i;
	int		fd;

	i = -1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	close(fd);
	return TRUE;
}