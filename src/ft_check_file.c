/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:47:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 12:15:42 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

int ft_check_file(char *file, t_state *state){

	int		i;
	int		fd;
	// char		*str;
	// char		*cut;
	int img[4];

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	// str = get_next_line(fd);
	i++;
	img[0] = 0; //no
	img[1] = 0; //so
	img[2] = 0; //we
	img[3] = 0; //ea
	// while (str != NULL)
	// {
	// 	if (i <= 4){
	// 		cut = ft_cut_space(str, 0);
	// 		if(ft_str_equals(cut, "NO") == TRUE)
	// 			img[0]++;
	// 		if(ft_str_equals(cut, "SO") == TRUE)
	// 			img[1]++;
	// 		if(ft_str_equals(cut, "WE") == TRUE)
	// 			img[2]++;
	// 		if(ft_str_equals(cut, "EA") == TRUE)
	// 			img[3]++;
	// 		ft_free(cut);
	// 	}
	// 	str = get_next_line(fd);
	// 	i++;
	// }
	close(fd);
	// if ((img[0] == 0 || img[0] > 1) || (img[1] == 0 || img[1] > 1) ||
	// 		(img[2] == 0 || img[2] > 1) || (img[3] == 0 || img[3] > 1))
	// 	return FALSE;
	return TRUE;
}