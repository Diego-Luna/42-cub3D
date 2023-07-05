/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:05:36 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/07/05 18:47:12 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

int main(int argc, char *argv[])
{
	t_state state;

	if (argc != 2 || ft_check_file(argv[1], &state) == FALSE)
		ft_error_print("🛑Error", &state);
	save_data(&state, argv[1]);
	(void)argc;
	(void)argv;
	return 0;
}
