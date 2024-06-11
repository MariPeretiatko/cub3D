#include "../../inc/cub3d.h"

void free_map(t_map *map){
    free_string_array(map->map);
    free(map->NO);
    free(map->EA);
    free(map->WE);
    free(map->SO);
    free(map->floor);
    free(map->ceiling);
    free(map);
}