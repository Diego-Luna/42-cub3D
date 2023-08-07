/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:05:36 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/07 16:23:16 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"

void	ft_print_map(t_state *state)
{
	int	i;

	i = 0;
	printf("\n\n --> map <--");
	while (state->map.map[i])
	{
		printf("\n ->{%s} w{%zu}", state->map.map[i],
			ft_strlen(state->map.map[i]));
		i++;
	}
	printf("\n -> map.width{%zu}", state->map.width);
	printf("\n -> map.height{%zu}", state->map.height);
	printf("\n --> map <--\n\n");
	printf("\n\n --> Path <--");
	printf("\n -> Path WE {%s}", state->map.path_we);
	printf("\n -> Path SO {%s}", state->map.path_so);
	printf("\n -> Path NO {%s}", state->map.path_no);
	printf("\n -> Path EA {%s}", state->map.path_ea);
	printf("\n\n --> Path <--");
	printf("\n\n --> Color <--");
	printf("\n -> COLOR C {%s}", state->map.c_color.s_color);
	printf("\n -> COLOR F {%s}", state->map.f_color.s_color);
	printf("\n --> Color <--\n\n");
}

void	ft_init_state_game(t_state *state)
{
	state->game.sky = NULL;
	state->game.floor = NULL;
	state->game.tex_no = NULL;
	state->game.img_no = NULL;
	state->game.tex_so = NULL;
	state->game.img_so = NULL;
	state->game.tex_we = NULL;
	state->game.img_we = NULL;
	state->game.tex_ea = NULL;
	state->game.img_ea = NULL;
	state->game.key = 0;
}

void	ft_init_state_map(t_state *state)
{
	state->map.path_no = NULL;
	state->map.path_so = NULL;
	state->map.path_we = NULL;
	state->map.path_ea = NULL;
	state->map.f_color.s_color = NULL;
	state->map.c_color.s_color = NULL;
	state->map.direccion = '\0';
	state->map.map = NULL;
}

void	ft_init_state(t_state *state)
{
	ft_init_state_map(state);
	ft_init_state_game(state);
	state->ray.dir_y = 0;
	state->ray.dir_x = 1;
	state->ray.plane_x = 0;
	state->ray.plane_y = 0.66;
	state->ray.time = 0;
	state->ray.old_time = 0;
	state->ray.g_img = NULL;
}

int32_t	main(int argc, char *argv[])
{
	t_state	state;

	(void)argc;
	(void)argv;
	ft_init_state(&state);
	if (argc != 2 || !ft_check_file(argv[1], &state))
		ft_error_print("error in file ", &state);
	ft_save_data(&state, argv[1]);
	ft_check_map(&state);
	ft_print_map(&state);
	ft_run_game(&state);
	printf("\n🤟 run 🤟\n");
	ft_free_state(&state);
	return (0);
}
