/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:10:27 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 12:00:04 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
#	include <fcntl.h>

# include "./libft/libft.h"

# define FALSE 0
# define TRUE 1

typedef struct s_state
{
	char *path_no;
	char *path_so;
	char *path_we;
	char *path_ea;
	char **map;
	int height;
	int width;
}				t_state;

// check file
int ft_check_file(char *file, t_state *state);

// Save data
void save_data(t_state *state, char *file);

// Error
void	ft_error_print(char *str, t_state *state);
void	ft_free_state(t_state *state);
char	*ft_free(char *src);

// str
char *ft_cut_space(char *str, size_t start);
int	ft_str_equals(char *str_1, char *str_2);

#endif