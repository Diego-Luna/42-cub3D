/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:08:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/14 13:12:50 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/cub.h"

int	ft_check_file_ext(char *file)
{
	size_t	i;
	char	*new;

	i = ft_strlen(file) - 1;
	while (i > 0 && file[i] != '.')
	{
		i--;
	}
	if (ft_strlen(file) - i > 4 || ft_strlen(file) - i < 3)
		return (FALSE);
	new = ft_substr(file, i, ft_strlen(file));
	if (ft_strncmp(".cub\0", new, ft_strlen(".cub\0")) != 0)
		return (free(new), FALSE);
	return (free(new), TRUE);
}
