/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:28 by mperetia          #+#    #+#             */
/*   Updated: 2024/06/15 00:04:11 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
# include <time.h>
# include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "get_next_line/gnl.h"
#include "../minilibx_linux/mlx.h"


# define MOVE_SPEED	0.02
# define ROTATION_SPEED 0.02


#  define KEY_W   119
#  define KEY_A   97
#  define KEY_S   115
#  define KEY_D   100
#  define KEY_ESC 65307
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  include <X11/keysym.h>


#define HEIGHT 1024
#define WIDTH 2048

#define PI 3.14

typedef struct s_dataList
{
    char *string;
    struct s_dataList *prev;
    struct s_dataList *next;
}t_dataList;

typedef struct s_player
{
    double posX;
    double posY;
    
}t_player;


typedef struct s_map
{
    char **map;
    int  start_map;
    int rows;
    int cols;
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char *floor;
    char *ceiling;
    unsigned int color_floor;
    unsigned int color_ceiling;
} t_map;

typedef struct s_raycast
{
   double posX;
   double posY;
   double dirX;
   double dirY;
   double planeX;
   double planeY;


   
   double time;
   double oldTime;

   
}t_raycast;
  

typedef struct s_game
{
    void		*mlx;
    void		*mlx_win;
    t_map		map;
    void		*wall;
    void		*floor;
//    t_exit		exit;
    void		*collectible;
//    t_character	character;
//    t_count		count_all;
//    t_enemy		**enemy;
    int			i;
}	t_game;



//free data
void free_map(t_map *map);

//valid_map
void valid_symbols(char **map);
//bool valid_map(char **map);
bool check_walls(char **map);
bool is_wall_error(char **map, int x, int y);
bool check_corners(char **map);

//dataList
t_dataList	*ft_lstlast(t_dataList *lst);
void	ft_lstadd_back(t_dataList **lst, t_dataList  *new);
t_dataList 	*ft_lstnew(char *str);
int	ft_lstsize(t_dataList  *start, t_dataList *end, int *cols);
void free_data_list(t_dataList *list);

//error
void error_exit(char *mes);
void print_data_list(t_dataList *data);

//global_utils
void free_string_array(char** string_array);
char *remove_symb(char *input_string, char symb);
char	*ft_strjoin(char const *s1, char const *s2); //? libft


//utils check map

int	check_map_name(const char *av);
void check_parameter(t_map *map, char **parameters);
void init_parameter(t_map *map, t_dataList *data);
bool is_one_or_space(const char *str);
t_dataList *check_start_map(t_map *map, t_dataList *data);
//char**	read_map(char *path);
t_dataList	*read_map(char *path);
void init_map(t_map *map, t_dataList *data);



//delete
char	**ft_split(char const *s, char c);
void print_data(char **data);
void print_test(t_map *map);

#endif
