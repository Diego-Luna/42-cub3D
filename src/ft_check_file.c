/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:47:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 16:43:36 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

int	ft_check_path(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_error_print("File not exists", NULL);
	}
	close(fd);
	return (TRUE);
}

int	ft_check_file_img(char *str, int *img)
{
	char	*cut;
	char	*cut_2;

	cut = ft_cut_space(str, 0);
	if (ft_str_equals(cut, "NO") == TRUE || ft_str_equals(cut, "SO") == TRUE
		|| ft_str_equals(cut, "WE") == TRUE || ft_str_equals(cut, "EA") == TRUE)
	{
		cut_2 = ft_cut_word(str, ' ', 2);
		printf("\n-> Diego cut_2{%s}", cut_2);
		if (ft_str_equals(cut, "NO") == TRUE)
			img[0]++;
		else if (ft_str_equals(cut, "SO") == TRUE)
			img[1]++;
		else if (ft_str_equals(cut, "WE") == TRUE)
			img[2]++;
		else if (ft_str_equals(cut, "EA") == TRUE)
			img[3]++;
		// ft_check_path(cut_2);
		ft_free(cut_2);
		if (ft_count_words(str, ' ') != 2)
			return (ft_free(cut), FALSE);
	}
	ft_free(cut);
	return (TRUE);
}

int	ft_check_file_check(t_state *state, int *img)
{
	(void)state;
	(void)img;
	if ((img[0] == 0 || img[0] > 1) || (img[1] == 0 || img[1] > 1)
		|| (img[2] == 0 || img[2] > 1) || (img[3] == 0 || img[3] > 1))
	{
		return (FALSE);
	}
	return (TRUE);
}

int	ft_check_file(char *file, t_state *state)
{
	int		fd;
	char	*str;
	int		img[4];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	img[0] = 0;
	img[1] = 0;
	img[2] = 0;
	img[3] = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (ft_check_file_img(str, img) == FALSE)
			return (ft_free(str), FALSE);
		ft_free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (ft_check_file_check(state, img));
}
