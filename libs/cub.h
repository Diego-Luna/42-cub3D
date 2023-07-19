/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:10:27 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/19 16:55:57 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define FALSE 0
# define TRUE 1

#define WIDTH 512
#define HEIGHT 512

typedef struct s_map
{
	char	*path_no;
	int	n_no;
	char	*path_so;
	int	n_so;
	char	*path_we;
	int	n_we;
	char	*path_ea;
	int	n_ea;
	char	**map;
	int		start_map;
	int		end_map;
	size_t		height;
	size_t		width;
}		t_map;

typedef struct s_state
{
	t_map map;
}			t_state;

// check file
int			ft_check_file(char *file, t_state *state);
int			ft_check_path(char *file);
int		ft_is_map(char *str);
int 	ft_check_map(t_state *state);

// Save data
void		ft_save_data(t_state *state, char *file);
void		ft_print_map(t_state *state);

// Error
void		ft_error_print(char *str, t_state *state);
void		ft_free_state(t_state *state);
char		*ft_free(char *src);

// str
char		*ft_cut_space(char *str, size_t start);
int			ft_str_equals(char *str_1, char *str_2);
char		*ft_cut_word(char *str, char cut, int number);
int			ft_count_words(char *str, char cut);
int			ft_str_is_number(char *str);

#endif