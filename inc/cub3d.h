/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:28 by mperetia          #+#    #+#             */
/*   Updated: 2024/06/12 22:26:13 by dyarkovs         ###   ########.fr       */
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


#define HEIGHT 800
#define WIDTH 1024

#define PI 3.14

typedef struct s_data_list
{
    char *string;
    struct s_data_list *prev;
    struct s_data_list *next;
}t_data_list;

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
bool is_wall_error(char **map, size_t x, int y);
bool check_corners(char **map);

//dataList
t_data_list	*ft_lstlast(t_data_list *lst);
void	ft_lstadd_back(t_data_list **lst, t_data_list  *new);
t_data_list 	*ft_lstnew(char *str);
int	ft_lstsize(t_data_list  *start, t_data_list *end);
void free_data_list(t_data_list *list);

//error
void error_exit(char *mes);
void print_data_list(t_data_list *data);

//global_utils
void free_string_array(char** string_array);
char *remove_symb(char *input_string, char symb);
char	*ft_strjoin(char const *s1, char const *s2); //? libft


//utils check map

int	check_map_name(const char *av);
void check_parameter(t_map *map, char **parameters);
void init_parameter(t_map *map, t_data_list *data);
bool is_one_or_space(const char *str);
t_data_list *check_start_map(t_map *map, t_data_list *data);
//char**	read_map(char *path);
t_data_list	*read_map(char *path);
void init_map(t_map *map, t_data_list *data);



//delete
char	**ft_split(char const *s, char c);
void print_data(char **data);
void print_test(t_map *map);

#endif
