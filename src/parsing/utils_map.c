#include "../../inc/cub3d.h"

int	check_map_name(const char *av)
{
    char	*name_map;

    name_map = strrchr(av, '.');
    if (name_map)
        return (!strcmp(name_map, ".cub"));
    return (0);
}


void check_parameter(t_map *map, char **parameters)
{
    if(!strcmp(parameters[0], "NO") && !map->NO)
        map->NO = remove_symb(parameters[1], '\n');
    else if(!strcmp(parameters[0], "SO") && !map->SO)
        map->SO = remove_symb(parameters[1], '\n');
    else if(!strcmp(parameters[0], "WE") && !map->WE)
        map->WE = remove_symb(parameters[1], '\n');
    else if(!strcmp(parameters[0], "EA") && !map->EA)
        map->EA = remove_symb(parameters[1], '\n');
    else if(!strcmp(parameters[0], "F") && !map->floor)
        map->floor = remove_symb(parameters[1], '\n');
    else if(!strcmp(parameters[0], "C") && !map->ceiling)
        map->ceiling = remove_symb(parameters[1], '\n');
    else
        error_exit("Incorrect parameters in the file");
}

int count_size_array(char **array){
    int count = 0;
    while (array[count])
        count++;
    return (count);
}

void init_parameter(t_map *map, t_data_list *data)
{
    char **parameters;
    int i = 0;
    while (i < map->start_map) {
        if (strcmp(data->string, "\n")) {
            parameters = ft_split(data->string, ' ');
            if (count_size_array(parameters) != 2) {
                error_exit("Invalid number of arguments in parameter");
            }
            check_parameter(map, parameters);
            free_string_array(parameters);
        }
        data = data->next;
        i++;
    }
}

bool is_one_or_space(const char *str)
{
    int i = 0;
    if(str[i] == '\n')
        return false;
    while (str[i]) {
        if (str[i] != '1' && str[i] != ' ' && str[i] != '\f' &&
        str[i] != '\n' && str[i] != '\r' && str[i] != '\t' && str[i] != '\v') {
            return false;
        }
        i++;
    }
    return true;
}

t_data_list *check_start_map(t_map *map, t_data_list *data)
{
    int i = 0;

    while(data){
        if(is_one_or_space(data->string)){
            map->start_map = i;
            return data;
        }
        data = data->next;
        i++;
    }
    return NULL;
}

t_data_list	*read_map(char *path)
{
    char	*line;
    int		fd;
    t_data_list *dataList = NULL;


    fd = open(path, O_RDONLY);
    if(fd == -1)
        error_exit("fd");
    while ((line = get_next_line(fd)) != NULL) {
        if (!dataList) {
            dataList = ft_lstnew(line);
        } else {
            ft_lstadd_back(&dataList, ft_lstnew(line));
        }
        free(line);
    }
    if (close(fd) == -1)
        error_exit("close");
    return dataList;
}

void check_all_init_params(t_map *map){
    if (!map->EA || !map->WE || !map->SO || !map->NO || !map->floor || !map->ceiling)
        error_exit("Not all parameters are initialized ");
}

t_data_list *check_last_map(t_map *map, t_data_list *dataList){
    t_data_list *last = ft_lstlast(dataList);

    while (!strcmp(last->string, "\n")){
        last = last->prev;
    }
//    printf("here\n %s", last->string);
    return last;
}

void init_map(t_map *map, t_data_list *data)
{
    t_data_list *last = check_last_map(map, data);
    printf("here\n %s", last->string);
    t_data_list *head = check_start_map(map, data);
    init_parameter(map, data);
    check_all_init_params(map);
    int i = 0;
    map->rows = ft_lstsize(head, last);
    printf("%d\n", map->rows);
    map->map = (char**)malloc((map->rows + 2) * sizeof(char*));
    while (head != last->next){
        map->map[i] = remove_symb(head->string, '\n');
        i++;
        head = head->next;
    }
    map->map[i] = NULL;
//    free_string_array(map->map);
}