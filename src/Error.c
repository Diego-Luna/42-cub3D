/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:12:20 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/05 18:48:38 by dluna-lo         ###   ########.fr       */
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

void	ft_free_state(t_state *state){
	size_t i = 0;

	ft_free(state->path_ea);
	ft_free(state->path_no);
	ft_free(state->path_so);
	ft_free(state->path_we);
	while (i < (size_t)state->height)
	{
		ft_free(state->map[i]);
		i++;
	}
	free(state->map);
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
