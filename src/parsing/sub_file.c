#include "../../inc/cub3d.h"

void print_data(char **data)
{
    int j = 0;
    if(data == NULL)
        return;
    while (data[j]){
        printf("%s\n", data[j]);
        j++;
    }
}

void print_data_list(t_data_list *data) {
    while (data) {
        printf("%s", data->string);
        data = data->next;
    }
}

void print_test(t_map *map){

//    printf("NO - %s\n", map->NO);
//    printf("SO - %s\n", map->SO);
//    printf("WE - %s\n", map->WE);
//    printf("EA - %s\n", map->EA);
//    printf("ceiling - %s\n", map->ceiling);
////    printf("floor - %s\n",  map->floor);
//    printf("floor - %s\n", map->floor);
////    printf("%s\n", map->map[0]);
////    printf("%s\n", map->map[0]);
////    printf("%s\n", map->map[1]);
    print_data(map->map);
//
//    printf("color_ceiling - %u\n", map->color_ceiling);
//    printf("color_floor - %u\n", map->color_floor);

}
