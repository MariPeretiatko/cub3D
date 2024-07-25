/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:28 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/25 17:58:17 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx_linux/mlx.h"
# include "libft/libft.h"
# include "libft/src/ft_printf/ft_printf.h"
# include "libft/src/get_next_line/get_next_line_bonus.h"
# include <X11/X.h>
# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define PINK 0xffc0cb
# define BLUE 0x0100fa
# define GREEN 0x00fa01
# define RED 0xfa0100
# define YELLOW 0xffff00
# define FL 0xa9a9a9
# define CEAL 0xf5f5f5

# define MOVE_SPEED 0.03
# define ROTATION_SPEED 0.02

# define SCREEN_WIDTH 1800
# define SCREEN_HEIGHT 1000

// # define texWidth 512
# define TEXWIDTH 512
// # define texHeight 512
# define TEXHEIGHT 512

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PRESS KeyPress
# define KEY_RELEASE KeyRelease

# define KEY_PRESS_MASK KeyPressMask
# define KEY_RELEASE_MASK KeyReleaseMask
# include <X11/keysym.h>

# define PI 3.14

enum					e_Cardinal
{
	EAST = 0,
	WEST,
	SOUTH,
	NORTH
};

enum					e_Error
{
	_EAST = 0,
	_WEST,
	_SOUTH,
	_NORTH
};

typedef struct s_dataList
{
	char				*string;
	struct s_dataList	*prev;
	struct s_dataList	*next;
}						t_dataList;

typedef struct s_map
{
	t_dataList			*data;
	char				**map;
	int					start_map;
	int					rows;
	int					cols;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*floor;
	char				*ceiling;
	unsigned int		color_floor;
	unsigned int		color_ceiling;
}						t_map;

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

typedef struct s_player
{
	char				direction;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
}						t_player;

typedef struct s_raycast
{
	double				camera_x;
	double				raydir_x;
	double				raydir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				wall_x;
	double				step;
	double				tex_pos;
	int					tex_x;
	int					tex_y;
	int					color;
}						t_raycast;

typedef struct s_pressed
{
	bool				left;
	bool				right;
	bool				w;
	bool				a;
	bool				s;
	bool				d;
}						t_pressed;
typedef struct s_game
{
	void				*mlx;
	void				*mlx_win;
	t_map				*map;
	t_player			player;
	t_raycast			rc;
	t_image				*back;
	t_pressed			pressed;
	t_image				*no_img;
	t_image				*so_img;
	t_image				*we_img;
	t_image				*ea_img;
}						t_game;

void					print_data(t_dataList *data);
void					init_game(t_map *map);
t_map					*check_init_map(char *path);
// free data
void					free_map(t_map *map);
void					free_game(t_game *game);
void					free_image(void *mlx_ptr, t_image *image);

// valid_map
bool					valid_symbol(char c);
bool					valid_symbol_character(char c);
void					valid_symbols(t_map *map);
void					check_valid_map(t_map *map);
// bool valid_map(char **map);
bool					check_walls(char **map);
bool					is_wall_error(char **map, int x, int y);
bool					check_corners(char **map);
bool					valid_symbol_character(char c);

// dataList
t_dataList				*ft_dbl_lstlast(t_dataList *lst);
void					ft_dbl_lstadd_back(t_dataList **lst, t_dataList *new);
t_dataList				*ft_dbl_lstnew(char *str);
int						ft_dbl_lstsize(t_dataList *start, t_dataList *end,
							int *cols);
void					free_data_list(t_dataList *list);

// error
void					error_exit(char *mes);
void					error_exit_game(char *mes, t_game *game);
void					error_exit_map(char *mes, t_map *map);
void					print_data_list(t_dataList *data);
void					error_exit_data_list(char *mes, t_dataList *data);
void					error_exit_map_array(char *mes, t_map *map,
							char **array);

// global_utils
void					free_string_array(char **string_array);
char					*remove_symb(char *input_string, char symb);
char					*ft_strjoin(char const *s1, char const *s2);
//? libft

// utils check map

int						check_map_name(const char *av);
void					check_parameter(t_map *map, char **parameters);
void					init_parameter(t_map *map, t_dataList *data);
bool					is_one_or_space(const char *str);
t_dataList				*check_start_map(t_map *map, t_dataList *data);
t_dataList				*check_last_map(t_dataList *dataList);
int						count_size_array(char **array);
bool					error_color(char **rgb, t_map *map, int j);
bool					check_all_init_params(t_map *map);
// char**	read_map(char *path);
t_dataList				*read_map(char *path);
void					init_map(t_map *map, t_dataList *data);

// delete
char					**ft_split(char const *s, char c);
// void					print_data(char **data);
void					print_test(t_map *map);

// raycast

int						key_action(int keycode, t_game *game);
bool					moves_execute(t_game *game);
int						key_release_hook(int keycode, t_game *game);
int						key_hook(int keycode, t_game *game);
void					move_right(t_game *game);
void					move_left(t_game *game);
void					rotate_left(t_game *game);
void					rotate_right(t_game *game);
void					move_back(t_game *game);
void					move_front(t_game *game);
int						render(t_game *game);
void					render_walls(t_game *game, int x, int y);
void					calculate_texture_coordinates(t_game *game);
void					calculate_wall_parameters(t_game *game);
void					set_ray_steps(t_game *game);
void					calculate_step_and_dist(t_game *game);
void					ray_direction_calculate(t_game *game, int x);
int						get_texture_pixel(t_image *texture, int texX, int texY);
int						get_pixel(t_image *img, int x, int y);
t_image					*get_texture_directions(t_game *game);
void					render_floor_and_ceiling(t_game *game);
void					add_plane_characters(t_game *game);
void					init_position_charactor(t_game *game);
void					my_mlx_pixel_put(t_image *image, int x, int y,
							int color);

void					init_south_texture(t_game *game);
void					init_walls(t_game *game);

#endif
