/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:10:27 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/06 21:59:28 by diegofranci      ###   ########.fr       */
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
# include <math.h>


# define FALSE 0
# define TRUE 1

#define WIDTH 512
#define HEIGHT 512
#define BPP sizeof(int32_t)

#define DIRECCION_NO 0
#define DIRECCION_WE 90
#define DIRECCION_SO 180
#define DIRECCION_EA 270

#define SIDE_N 1
#define SIDE_W 2
#define SIDE_S 3
#define SIDE_E 4

#define WINDOW_W 500
#define WINDOW_H 500
# define texWidth 128
# define texHeight 128

typedef struct s_color{
	char *s_color;
	int r;
	int g;
	int b;
	int a;
} t_color;

typedef struct s_player{
	double x;
	double y;
	double angle;
} t_player;

typedef struct s_raycasting{
	double dirX; //initial direction vector
	double dirY; //initial direction vector
	double planeX; //the 2d raycaster version of camera plane
	double planeY; //the 2d raycaster version of camera plane
	double time; //time of current frame
	double oldTime; //time of previous frame

	double cameraX; //x-coordinate in camera space
	double rayDirX; //direction of ray on x-axis
	double rayDirY; //direction of ray on y-axis
	mlx_image_t *g_img;
} t_raycasting;

typedef struct s_map
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char direccion;
	char	**map;
	int		start_map;
	int		end_map;
	t_color f_color;
	t_color c_color;
	size_t		height;
	size_t		width;
}		t_map;

typedef struct s_game
{
	int key;
	int width;
	int height;
	mlx_t* mlx;
	mlx_image_t *sky;
	mlx_image_t *floor;
	mlx_texture_t* tex_no;
	mlx_image_t* img_no;
	mlx_texture_t* tex_so;
	mlx_image_t* img_so;
	mlx_texture_t* tex_we;
	mlx_image_t* img_we;
	mlx_texture_t* tex_ea;
	mlx_image_t* img_ea;
}		t_game;

typedef struct s_state
{
	t_map map;
	t_player player;
	t_game game;
	t_raycasting ray;
}			t_state;

typedef struct s_info_recursive
{
	int		n_collec;
	int		x_max;
	int		y_max;
	char	**map;
	char	is_path_exit;
	char	is_posible;
}			t_recursive;

// check file
int			ft_check_file(char *file, t_state *state);
int			ft_check_path(char *file);
int		ft_is_map(char *str);
int 	ft_check_map(t_state *state);
void	ft_map_validity(t_state *state, void (*f)(t_state *, char, size_t,
			size_t));

// Save data
void		ft_save_data(t_state *state, char *file);
void		ft_print_map(t_state *state);

// Error
void		ft_error_print(char *str, t_state *state);
void		ft_free_state(t_state *state);
char	**ft_free_table(char **src);
char		*ft_free(char *src);

// str
char		*ft_cut_space(char *str, size_t start);
int			ft_str_equals(char *str_1, char *str_2);
char		*ft_cut_word(char *str, char cut, int number);
int			ft_count_words(char *str, char cut);
int			ft_str_is_number(char *str);

// Game
void	ft_rendering(void *param);
void ft_run_game(t_state *state);
void ft_init_game(t_state *state);
void	ft_creat_frams(t_state *state);
int get_rgba(int r, int g, int b, int a);
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	ft_change_full_color(mlx_image_t *image, int r, int g, int b);
void	my_keyhook_rotate_left(t_state *state, mlx_key_data_t keydata,
		double rot_speed);
void	my_keyhook_rotate_right(t_state *state, mlx_key_data_t keydata,
		double rot_speed);
int	ft_movent_posiblel_ws(t_state *state, int redreccion, double movent_speed);
int	ft_movent_posiblel_ad(t_state *state, int redreccion, double movent_speed);

// raycasting
void  ft_raycasting(t_state *state);

// void	ft
void	ft_complete_map(char **map);
int	ft_valid_info(char c);

#endif