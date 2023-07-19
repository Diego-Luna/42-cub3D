/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:05:36 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/19 16:08:31 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

void		ft_print_map(t_state *state){
	int i;

	i = 0;
	ft_printf("\n\n --> map <--");
	while (state->map.map[i])
	{
		ft_printf("\n ->{%s} w{%d}", state->map.map[i], ft_strlen(state->map.map[i]));
		i++;
	}
	ft_printf("\n --> map <--\n\n");
}

int32_t	main(int argc, char *argv[])
{
	t_state	state;

	state.map.path_no = NULL;
	state.map.path_so = NULL;
	state.map.path_we = NULL;
	state.map.path_ea = NULL;
	state.map.map = NULL;
	if (argc != 2 || !ft_check_file(argv[1], &state))
		ft_error_print("error in file ", &state);
	ft_save_data(&state, argv[1]);
	ft_check_map(&state);
	ft_print_map(&state);
	printf("\n🤟 run 🤟\n");
	ft_free_state(&state);
	return (0);
}
