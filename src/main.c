/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:05:36 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/18 18:53:01 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

void		ft_print_map(t_state *state){
	int i;

	i = 0;
	ft_printf("\n\n --> map <--");
	while (state->map[i])
	{
		ft_printf("\n ->{%s} w{%d}", state->map[i], ft_strlen(state->map[i]));
		i++;
	}
	ft_printf("\n --> map <--\n\n");
}

int	main(int argc, char *argv[])
{
	t_state	state;

	state.path_no = NULL;
	state.path_so = NULL;
	state.path_we = NULL;
	state.path_ea = NULL;
	state.map = NULL;
	if (argc != 2 || !ft_check_file(argv[1], &state))
		ft_error_print("error in file ", &state);
	ft_save_data(&state, argv[1]);
	ft_check_map(&state);
	ft_print_map(&state);
	printf("\n🤟 run 🤟\n");
	ft_free_state(&state);
	return (0);
}
