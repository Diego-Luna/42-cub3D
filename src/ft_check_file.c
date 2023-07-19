/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:47:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/18 16:20:23 by dluna-lo         ###   ########.fr       */
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

int	ft_check_file_color(char *str, int *img)
{
	char	*cut;
	char	*cut_2;
	char	*cut_3;

	img[4] = 0;
	cut = ft_cut_space(str, 0);
	if (ft_str_equals(cut, "F") == TRUE || ft_str_equals(cut, "C") == TRUE)
	{
		if (ft_count_words(str, ' ') != 2)
			return (ft_free(cut), FALSE);
		cut_2 = ft_cut_word(str, ' ', 2);
		cut = ft_free(cut);
		if (ft_count_words(cut_2, ',') != 3)
			return (ft_free(cut_2), FALSE);
		while (img[4] < 3)
		{
			cut_3 = ft_cut_word(cut_2, ',', img[4] + 1);
			if (ft_strlen(cut_3) > 3 || ft_str_is_number(cut_3) == FALSE
				|| (ft_atoi(cut_3) < 0 || ft_atoi(cut_3) > 255))
				return (ft_free(cut_2), ft_free(cut_3), FALSE);
			ft_free(cut_3);
			img[4]++;
		}
		ft_free(cut_2);
		img[5]++;
		return (ft_free(cut), TRUE);
	}
	return (ft_free(cut), FALSE);
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
	if (img[5] != 2)
		return (FALSE);
	if ((img[0] == 0 || img[0] > 1) || (img[1] == 0 || img[1] > 1)
		|| (img[2] == 0 || img[2] > 1) || (img[3] == 0 || img[3] > 1))
	{
		return (FALSE);
	}
	return (line);
}

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

int	ft_check_file_img_color(char *file, t_state *state)
{
	int		fd;
	char	*str;
	int		img[6];
	int		ft[3];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_print("File not exists", state);
	img[0] = 0;
	img[1] = 0;
	img[2] = 0;
	img[3] = 0;
	img[5] = 0;
	ft[2] = 0;
	str = get_next_line(fd);
	ft[2]++;
	while (str != NULL)
	{
		ft[0] = ft_check_file_img(str, img);
		ft[1] = ft_check_file_color(str, img);
		if ((ft[0] == FALSE && ft[1] == FALSE
				&& ft_check_file_emptyline(str) == FALSE) || (ft[0] == TRUE
				&& ft[1] == TRUE && ft_check_file_emptyline(str) == FALSE))
		{
			break ;
		}
		str = ft_free(str);
		str = get_next_line(fd);
		ft[2]++;
	}
	str = ft_free(str);
	close(fd);
	return (ft_check_file_check(state, img, ft[2]));
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
	state->start_map = i[1];
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
	state->end_map = i[0];
	close(fd);
	return (map);
}
