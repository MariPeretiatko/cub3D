/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:28 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/04 19:52:50 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx_linux/mlx.h"
# include "get_next_line/gnl.h"
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
#  include <X11/X.h>

#define PINK 0xffc0cb
#define BLUE 0x0100fa
#define GREEN 0x00fa01
#define RED 0xfa0100
#define YELLOW 0xffff00
#define FL 0xa9a9a9
#define CEAL 0xf5f5f5

# define MOVE_SPEED 0.3
# define ROTATION_SPEED 0.2

# define SCREEN_WIDTH 2048
# define SCREEN_HEIGHT 1024

# define texWidth 64
# define texHeight 64

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
#  define KEY_PRESS         KeyPress
#  define KEY_RELEASE       KeyRelease

#  define KEY_PRESS_MASK	KeyPressMask
#  define KEY_RELEASE_MASK	KeyReleaseMask
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
	char				**map;
	int					start_map;
	int					rows;
	int					cols;
	char				*NO;
	char				*SO;
	char				*WE;
	char				*EA;
	char				*floor;
	char				*ceiling;
	unsigned int		color_floor;
	unsigned int		color_ceiling;
}						t_map;

typedef struct s_texture
{
	int					width;
	int					height;
	unsigned char		*pixels;
}						t_texture;
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
}						t_raycast;

typedef struct s_pressed
{
	bool				left;
	bool				right;
	bool				W;
	bool				A;
	bool				S;
	bool				D;
}						t_pressed;
typedef struct s_game
{
	void				*mlx;
	void				*mlx_win;
	t_map				*map;
	void				*wall;
	void				*floor;
	t_player			player;
	t_raycast			rc;
	t_image				back;
	t_pressed 			pressed;
}						t_game;

// free data
void					free_map(t_map *map);

// valid_map
void					valid_symbols(char **map);
// bool valid_map(char **map);
bool					check_walls(char **map);
bool					is_wall_error(char **map, int x, int y);
bool					check_corners(char **map);
bool					valid_symbol_character(char c);

// dataList
t_dataList				*ft_lstlast(t_dataList *lst);
void					ft_lstadd_back(t_dataList **lst, t_dataList *new);
t_dataList				*ft_lstnew(char *str);
int						ft_lstsize(t_dataList *start, t_dataList *end,
							int *cols);
void					free_data_list(t_dataList *list);

// error
void					error_exit(char *mes);
void					print_data_list(t_dataList *data);

// global_utils
void					free_string_array(char **string_array);
char					*remove_symb(char *input_string, char symb);
char	*ft_strjoin(char const *s1, char const *s2); //? libft

// utils check map

int						check_map_name(const char *av);
void					check_parameter(t_map *map, char **parameters);
void					init_parameter(t_map *map, t_dataList *data);
bool					is_one_or_space(const char *str);
t_dataList				*check_start_map(t_map *map, t_dataList *data);
// char**	read_map(char *path);
t_dataList				*read_map(char *path);
void					init_map(t_map *map, t_dataList *data);

// delete
char					**ft_split(char const *s, char c);
void					print_data(char **data);
void					print_test(t_map *map);

#endif
