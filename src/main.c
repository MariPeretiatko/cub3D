#include "../inc/cub3d.h"



int main(int ac, char *av[]){
    if (ac != 2)
        error_exit("problems with arguments");
    if (!check_map_name(av[1]))
        error_exit("Can't open file. The format is not supported!");

    t_data_list *data = read_map(av[1]);
    if (!data) {
        error_exit("Error reading map");
    }

    t_map *map = calloc(1, sizeof(t_map));
    if (!map) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    init_map(map, data);
    // t_game *game = calloc(1, sizeof(t_game));

    // game->mlx = mlx_init();
    // read_map(game, path);
    // game->mlx_win = mlx_new_window(game->mlx, game->map.width * 32,
    //                                game->map.height * 32 + 20, "SO_LONG");
    // init_textures(game);
    // init_counter(game);
    // init_map(game);
    // check_path_finder(game, path);
    // check_map_error_count(game);
    // add_counter(game);
    // mlx_hook(game->mlx_win, 17, 1L << 0, exit_game, game);
    // mlx_key_hook(game->mlx_win, key_action, game);
    // mlx_loop(game->mlx);
    // free(game);
//    free_data_list(data);
//    free_map(map);
//    free(map);
//    valid_symbols(map->map);
//    print_test(map);
//    print_data_list(data);
//    if (check_walls(map->map))
//        return (printf("Error: Empty space exists\n"), 1);
//    if (check_corners(map->map))
//        return (printf("Error: Empty corner exists\n"), 1);

    return (0);
}