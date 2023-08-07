/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:14:12 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:14:13 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int	ft_check_file_color_if(char *cut_3)
{
	if (ft_strlen(cut_3) > 3 || ft_str_is_number(cut_3) == FALSE
		|| (ft_atoi(cut_3) < 0 || ft_atoi(cut_3) > 255))
	{
		return (TRUE);
	}
	return (FALSE);
}

void	ft_check_file_color_utils_1(char *cut, int *img)
{
	if (ft_str_equals(cut, "F") == TRUE)
	{
		img[6]++;
	}
	if (ft_str_equals(cut, "C") == TRUE)
	{
		img[7]++;
	}
}

int	ft_check_file_color_utils_2(char *cut_2, int *img, char *cut)
{
	ft_free(cut_2);
	ft_free(cut);
	img[5]++;
	return (TRUE);
}

int	ft_check_file_color_utils_3(int *img, char *cut_3, char *cut_2, char *cut)
{
	while (img[4] < 3)
	{
		cut_3 = ft_cut_word(cut_2, ',', img[4] + 1);
		if (ft_check_file_color_if(cut_3) == TRUE)
		{
			ft_free(cut_2);
			ft_free(cut_3);
			return (FALSE);
		}
		ft_free(cut_3);
		img[4]++;
	}
	return (ft_check_file_color_utils_2(cut_2, img, cut));
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
		ft_check_file_color_utils_1(cut, img);
		if (ft_count_words(str, ' ') != 2)
			return (ft_free(cut), FALSE);
		cut_2 = ft_cut_word(str, ' ', 2);
		cut = ft_free(cut);
		if (ft_count_words(cut_2, ',') != 3)
			return (ft_free(cut_2), FALSE);
		cut_3 = NULL;
		return (ft_check_file_color_utils_3(img, cut_3, cut_2, cut));
	}
	return (ft_free(cut), FALSE);
}
