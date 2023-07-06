/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:12:20 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 12:34:49 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

void ft_exit(int error){
	exit(error);
}

void ft_error_print(char *str, t_state *state){
	char *ms;

	ms = ft_strjoin("Error: ", str);
	ft_putendl_fd(ms, 2);
	ft_free(ms);
	ft_free_state(state);
	ft_exit(1);
}

char	*ft_free(char *src)
{
	if (!src)
	{
		return (NULL);
	}
	if (src)
	{
		free(src);
	}
	return (NULL);
}

char	**ft_free_table(char **src)
{
	size_t i = 0;

	if (!src)
	{
		return (NULL);
	}
	while (src[i])
	{
		ft_free(src[i]);
		i++;
	}
	free(src);
	return (NULL);
}

void	ft_free_state(t_state *state){
	ft_free(state->path_ea);
	ft_free(state->path_no);
	ft_free(state->path_so);
	ft_free(state->path_we);
	ft_free_table(state->map);
}
