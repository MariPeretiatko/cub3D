/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:28 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/26 15:44:21 by mperetia         ###   ########.fr       */
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
# define REDD 0xfa0100
# define YELLOW 0xffff00
# define FL 0xa9a9a9
# define CEAL 0xf5f5f5

# define RESET "\033[0m"
# define RED "\033[1;31m"

# define MOVE_SPEED 0.03
# define ROTATION_SPEED 0.02

# define SCREEN_WIDTH 1800
# define SCREEN_HEIGHT 1000

# define TEXWIDTH 512
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

// dataList
// parsing/list.c
t_dataList				*ft_dbl_lstlast(t_dataList *lst);
void					ft_dbl_lstadd_back(t_dataList **lst,
							t_dataList *new_list);
t_dataList				*ft_dbl_lstnew(char *content);
int						ft_dbl_lstsize(t_dataList *start, t_dataList *end,
							int *cols);
void					free_data_list(t_dataList *head);

// valid_map
// parsing/check_map.c || valid_map.c || valid_symbol.c
int						check_map_name(const char *av);
bool					valid_symbol(char c);
void					valid_symbols(t_map *map);
void					check_valid_map(t_map *map);
bool					valid_symbol_character(char c);

// init_map
// parsing/check_map.c ||
t_map					*check_init_map(char *path);
t_dataList				*read_map(char *path);
bool					check_all_init_params(t_map *map);
t_dataList				*check_start_map(t_map *map, t_dataList *data);
t_dataList				*check_last_map(t_dataList *dataList);

// global_utils_parsing
// parsing/utils.c
int						count_size_array(char **array);
bool					error_color(char **rgb, t_map *map, int j);
char					*remove_symb(char *input_string, char symb);
bool					is_one_or_space(const char *str);

// raycasting
// raycast/raycast.c || render.c
int						render(t_game *game);
void					ray_direction_calculate(t_game *game, int x);
void					calculate_step_and_dist(t_game *game);
void					set_ray_steps(t_game *game);
void					calculate_wall_parameters(t_game *game);
void					calculate_texture_coordinates(t_game *game);

// utils raycasting
// raycast/utils_raycast.c
void					my_mlx_pixel_put(t_image *image, int x, int y,
							int color);
int						get_texture_pixel(t_image *texture, int tex_x,
							int tex_y);
void					add_plane_characters(t_game *game);
t_image					*get_texture_directions(t_game *game);

// init_game
// game/init_game.c || init_wals.c
void					init_game(t_map *map);
void					init_walls(t_game *game);

// key_action
// game/input_game.c || movement_game.c || rotate_game.c
int						key_action(int keycode, t_game *game);
int						key_release_hook(int keycode, t_game *game);
int						key_hook(int keycode, t_game *game);
void					move_right(t_game *game);
void					move_left(t_game *game);
void					rotate_left(t_game *game);
void					rotate_right(t_game *game);
void					move_back(t_game *game);
void					move_front(t_game *game);
bool					moves_execute(t_game *game);

// error
// error.c
void					error_exit(char *mes);
void					error_exit_game(char *mes, t_game *game);
void					error_exit_map(char *mes, t_map *map);
void					error_exit_data_list(char *mes, t_dataList *data);
void					error_exit_map_array(char *mes, t_map *map,
							char **array);

// global free data
// free.c
void					free_string_array(char **array);
void					free_map(t_map *map);
void					free_game(t_game *game);
void					free_image(void *mlx, t_image *image);
void					free_data_list(t_dataList *head);

#endif
