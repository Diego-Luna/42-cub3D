/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:11:50 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 17:08:10 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

char	*ft_cut_space(char *str, size_t start)
{
	int		word;
	size_t	end;
	size_t	i;

	word = 0;
	end = start;
	i = start;
	if (start >= ft_strlen(str))
		return (NULL);
	while (str[i] && word != 2)
	{
		if (word == 0 && str[i] != ' ')
		{
			word = 1;
			start = i;
		}
		if (word == 1 && str[i] == ' ')
		{
			word = 2;
			end = i;
		}
		i++;
	}
	return (ft_substr(str, start, (end)-start));
}

int	ft_str_equals(char *str_1, char *str_2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str_1) != ft_strlen(str_2))
		return (FALSE);
	while (str_1[i])
	{
		if (str_1[i] != str_2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void ft_cut_word_utils_1(size_t *start, size_t i, size_t *end){
	start = &i;
	end = 0;
}
void ft_cut_word_utils_2(int *nu, size_t i, size_t *end){
	end = &i;
	nu--;
}

char	*ft_cut_word(char *st, char cu, int nu)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	end = 0;
	while (st[i])
	{
		if (st[i] != cu && st[i] != '\n' && st[i] != '\0' && nu > 0 && end != 0)
			ft_cut_word_utils_1(&start, i , &end)
		else if ((st[i] == cu || st[i] == '\n' || st[i] == '\0') && nu > 0)
			ft_cut_word_utils_2(&nu, i, &end);
		i++;
	}
	if (nu != 0)
		return (NULL);
	return (ft_substr(st, start, end - start));
}

// char	*ft_cut_word(char *str, char cut, int number)
// {
// 	size_t	i;
// 	size_t	start;
// 	size_t	end;
// 	int		word;

// 	i = 0;
// 	start = 0;
// 	end = 0;
// 	word = FALSE;
// 	if (number <= 0)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (word == FALSE && str[i] != cut && number > 0)
// 		{
// 			start = i;
// 			word = TRUE;
// 		}
// 		if (word == TRUE && (str[i] == cut || str[i] == '\n') && number > 0)
// 		{
// 			end = i;
// 			word = FALSE;
// 			number--;
// 		}
// 		i++;
// 	}
// 	if (number != 0)
// 		return (NULL);
// 	// printf("\n --> Diego number{%d} start{%zu} end{%zu}",number,  start, end);
// 	return (ft_substr(str, start, end - start));
// }

int	ft_count_words(char *str, char cut)
{
	size_t i = 0;
	int number = 0;
	int word = FALSE;

	while (str[i])
	{
		if (word == FALSE && str[i] != cut)
			word = TRUE;
		if (word == TRUE && (str[i] == cut || str[i] == '\n'))
		{
			word = FALSE;
			number++;
		}
		i++;
	}
	return (number);
}