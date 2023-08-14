/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:47:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/11 12:45:21 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

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
		if (ft_str_equals(cut, "NO") == TRUE)
			img[0]++;
		else if (ft_str_equals(cut, "SO") == TRUE)
			img[1]++;
		else if (ft_str_equals(cut, "WE") == TRUE)
			img[2]++;
		else if (ft_str_equals(cut, "EA") == TRUE)
			img[3]++;
		ft_check_path(cut_2);
		ft_free(cut_2);
		if (ft_count_words(str, ' ') != 2)
			return (ft_free(cut), FALSE);
		return (ft_free(cut), TRUE);
	}
	return (ft_free(cut), FALSE);
}

int	ft_check_file_check(t_state *state, int *img, int line)
{
	(void)state;
	if (img[5] != 2 || img[6] != 1 || img[7] != 1)
		return (FALSE);
	if ((img[0] == 0 || img[0] > 1) || (img[1] == 0 || img[1] > 1)
		|| (img[2] == 0 || img[2] > 1) || (img[3] == 0 || img[3] > 1))
	{
		return (FALSE);
	}
	return (line);
}

int	ft_is_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0' && str[i] != '\n'
			&& !(str[i] == 'N' || str[i] == 'S' || str[i] == 'E'
				|| str[i] == 'W'))
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_check_file(char *file, t_state *state)
{
	int		fd;
	int		map;
	char	*str;
	int		i[2];

	i[1] = ft_check_file_img_color(file, state);
	if (i[1] == FALSE)
		return (FALSE);
	state->map.start_map = i[1];
	i[0] = 0;
	map = TRUE;
	fd = open(file, O_RDONLY);
	i[0]++;
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (i[0] >= i[1] && ft_is_map(str) == FALSE)
			map = FALSE;
		str = ft_free(str);
		str = get_next_line(fd);
		i[0]++;
	}
	state->map.end_map = i[0];
	close(fd);
	return (map);
}
