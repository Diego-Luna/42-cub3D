/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:12:46 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:12:46 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_cut_word_utils_2(size_t i, size_t *end, int *number, int *word)
{
	(*end) = i;
	(*number)--;
	(*word) = FALSE;
}

void	ft_cut_word_utils_1(size_t	*start, size_t	i, int		*word)
{
	(*start) = (i);
	(*word) = TRUE;
}

char	*ft_cut_word_utils_3(char *str, size_t	start, size_t	end, int number)
{
	if (number != 0)
		return (NULL);
	return (ft_substr(str, start, end - start));
}

void	ft_cut_word_utils_4(size_t	*end, size_t	i, int	*number)
{
	(*end) = i;
	(*number)--;
}

char	*ft_cut_word(char *str, char cut, int number)
{
	size_t	i;
	size_t	start;
	size_t	end;
	int		word;

	i = -1;
	start = 0;
	end = 0;
	word = FALSE;
	if (number <= 0)
		return (NULL);
	while (str[++i])
	{
		if (word == FALSE && str[i] != cut && number > 0)
		{
			ft_cut_word_utils_1(&start, i, &word);
		}
		if (word == TRUE && (str[i] == cut || str[i] == '\n') && number > 0)
			ft_cut_word_utils_2(i, &end, &number, &word);
	}
	if (word == TRUE)
		ft_cut_word_utils_4(&end, i, &number);
	return (ft_cut_word_utils_3(str, start, end, number));
}
