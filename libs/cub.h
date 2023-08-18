/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:10:27 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/18 17:59:26 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1

# define WIDTH 512
# define HEIGHT 512

# define DIRECCION_NO 0
# define DIRECCION_WE 90
# define DIRECCION_SO 180
# define DIRECCION_EA 270

# define SIDE_N 1
# define SIDE_W 2
# define SIDE_S 3
# define SIDE_E 4

# define WINDOW_W 500
# define WINDOW_H 500

typedef struct s_color
{
	char			*s_color;
	int				r;
	int				g;
	int				b;
	int				a;
}					t_color;

typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
}					t_player;

typedef struct s_raycasting
{
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			time;
	double			old_time;

	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	mlx_image_t		*g_img;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			cell_size;
	double			wall_x;
	int				tex_x;
	int				tex_y;
}					t_raycasting;

typedef struct s_map
{
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	char			direccion;
	char			**map;
	int				start_map;
	int				end_map;
	t_color			f_color;
	t_color			c_color;
	size_t			height;
	size_t			width;
}					t_map;

typedef struct s_game
{
	int				key;
	int				width;
	int				height;
	mlx_t			*mlx;
	mlx_image_t		*sky;
	mlx_image_t		*floor;
	mlx_texture_t	*tex_no;
	mlx_image_t		*img_no;
	mlx_texture_t	*tex_so;
	mlx_image_t		*img_so;
	mlx_texture_t	*tex_we;
	mlx_image_t		*img_we;
	mlx_texture_t	*tex_ea;
	mlx_image_t		*img_ea;
}					t_game;

typedef struct s_state
{
	t_map			map;
	t_player		player;
	t_game			game;
	t_raycasting	ray;
	int				error;
}					t_state;

typedef struct s_info_recursive
{
	int				n_collec;
	int				x_max;
	int				y_max;
	char			**map;
	char			is_path_exit;
	char			is_posible;
}					t_recursive;

// check file
void				ft_is_map_check_user(t_state *state, char c, size_t y,
						size_t x);
void				ft_is_map_check(t_state *state, char c, size_t y, size_t x);
void				ft_is_map_check_zeros(t_state *state, char c, size_t y,
						size_t x);
int					ft_check_file_ext(char *file);
int					ft_check_file(char *file, t_state *state);
int					ft_check_path(char *file);
size_t				ft_is_map(char *str);
int					ft_check_map(t_state *state);
int					ft_check_file_img_color(char *file, t_state *state);
int					ft_check_file_img(char *str, int *img);
int					ft_check_file_color(char *str, int *img);
int					ft_check_file_check(t_state *state, int *img, int line);
void				ft_map_validity(t_state *state, void (*f)(t_state *, char,
							size_t, size_t));

// Save data
void				ft_save_data(t_state *state, char *file);
void				ft_print_map(t_state *state);
void				ft_save_data(t_state *state, char *file);
void				ft_save_map(t_state *state, char *file);
void				ft_get_map_heigth(t_state *state, char *file);

// Error
void				ft_error_print(char *str, t_state *state);
void				ft_free_state(t_state *state);
char				**ft_free_table(char **src);
char				*ft_free(char *src);

// str
char				*ft_cut_space(char *str, size_t start);
int					ft_str_equals(char *str_1, char *str_2);
char				*ft_cut_word(char *str, char cut, int number);
int					ft_count_words(char *str, char cut);
int					ft_str_is_number(char *str);

// Game
void				ft_create_texture(t_state *state);
void				ft_rendering(void *param);
void				ft_run_game(t_state *state);
void				ft_init_game(t_state *state);
void				ft_creat_frams(t_state *state);
int					get_rgba(int r, int g, int b, int a);
void				my_keyhook(mlx_key_data_t keydata, void *param);
void				ft_change_full_color(mlx_image_t *image, int r, int g,
						int b);
void				my_keyhook_rotate_left(t_state *state,
						mlx_key_data_t keydata, double rot_speed);
void				my_keyhook_rotate_right(t_state *state,
						mlx_key_data_t keydata, double rot_speed);
int					ft_movent_posiblel_ws(t_state *state, int redreccion,
						double movent_speed);
int					ft_movent_posiblel_ad(t_state *state, int redreccion,
						double movent_speed);
void				ft_position_player(t_state *state, char c);

// raycasting
void				ft_raycasting(t_state *state);
void				ft_start_raycasting(t_state *state, int x);
void				ft_calculate_step_and_initial(t_state *state);

// void	ft
void				ft_complete_map(char **map);
int					ft_valid_info(char c);
void				ft_dda(t_state *state);
void				ft_distance_camera_direction(t_state *state, int x);

#endif