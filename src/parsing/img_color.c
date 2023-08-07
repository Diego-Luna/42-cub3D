/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:13:56 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:13:56 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int	ft_check_file_emptyline(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] != ' ' && file[i] != '\t' && file[i] != '\n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*ft_check_file_img_color_utils_1(int *img, int *ft, int fd)
{
	char	*str;

	img[0] = 0;
	img[1] = 0;
	img[2] = 0;
	img[3] = 0;
	img[5] = 0;
	img[6] = 0;
	img[7] = 0;
	ft[2] = 0;
	str = get_next_line(fd);
	ft[2]++;
	return (str);
}

int	ft_check_file_img_color_if(int *ft, char *str)
{
	if ((ft[0] == FALSE && ft[1] == FALSE
			&& ft_check_file_emptyline(str) == FALSE) || (ft[0] == TRUE
			&& ft[1] == TRUE && ft_check_file_emptyline(str) == FALSE))
	{
		return (TRUE);
	}
	return (FALSE);
}

int	ft_check_file_img_color(char *file, t_state *state)
{
	int		fd;
	char	*str;
	int		img[8];
	int		ft[3];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	str = ft_check_file_img_color_utils_1(img, ft, fd);
	while (str != NULL)
	{
		ft[0] = ft_check_file_img(str, img);
		ft[1] = ft_check_file_color(str, img);
		if (ft_check_file_img_color_if(ft, str) == TRUE)
			break ;
		str = ft_free(str);
		str = get_next_line(fd);
		ft[2]++;
	}
	str = ft_free(str);
	close(fd);
	return (ft_check_file_check(state, img, ft[2]));
}
