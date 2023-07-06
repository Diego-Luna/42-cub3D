/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:05:36 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/06 12:35:07 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

int main(int argc, char *argv[])
{
	t_state state;

	state.path_no = NULL;
	state.path_so = NULL;
	state.path_we = NULL;
	state.path_ea = NULL;
	state.map = NULL;
	if (argc != 2 || ft_check_file(argv[1], &state) == FALSE)
		ft_error_print("🛑Error", &state);
	// save_data(&state, argv[1]);
	ft_free_state(&state);
	(void)argc;
	(void)argv;
	return 0;
}
