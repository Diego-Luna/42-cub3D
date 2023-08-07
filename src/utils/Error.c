/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:12:20 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:12:56 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

void	ft_exit(int error)
{
	exit(error);
}

void	ft_error_print(char *str, t_state *state)
{
	char	*msg;

	if (str)
	{
		msg = ft_strjoin("🛑 Error: ", str);
		ft_putendl_fd(msg, 2);
		ft_free(msg);
	}
	if (state)
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
	size_t	i;

	i = 0;
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

void	ft_free_state(t_state *state)
{
	ft_free(state->map.path_ea);
	ft_free(state->map.path_no);
	ft_free(state->map.path_so);
	ft_free(state->map.path_we);
	ft_free(state->map.f_color.s_color);
	ft_free(state->map.c_color.s_color);
	ft_free_table(state->map.map);
	if (state->game.tex_no)
		mlx_delete_texture(state->game.tex_no);
	if (state->game.tex_so)
		mlx_delete_texture(state->game.tex_so);
	if (state->game.tex_we)
		mlx_delete_texture(state->game.tex_we);
	if (state->game.tex_ea)
		mlx_delete_texture(state->game.tex_ea);
}
