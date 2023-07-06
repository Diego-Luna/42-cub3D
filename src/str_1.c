/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:11:50 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 12:05:46 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

char *ft_cut_space(char *str, size_t start){
	int word = 0;
	size_t end = start;
	size_t i = start;

	if (start >= ft_strlen(str))
		return NULL;
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
	return ft_substr(str, start, (end)- start);
}

int	ft_str_equals(char *str_1, char *str_2)
{
	size_t i;

	i = 0;
	if (ft_strlen(str_1) != ft_strlen(str_2))
		return FALSE;
	while(str_1[i])
	{
		if (str_1[i] != str_2[i])
			return FALSE;
		i++;
	}
	return TRUE;
}
