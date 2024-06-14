#include "../inc/cub3d.h"

int	key_hook(int keycode, t_game *game)
{
    if(KEY_ESC == keycode)
        exit(0);//exit + free all;
    (void)game;
	printf("%d\n", keycode);
		// exit_game();
	return (0);
}

int	key_action(int keycode, t_game *game)
{
	if (KEY_A == keycode || KEY_LEFT == keycode || KEY_D == keycode
		|| KEY_RIGHT == keycode || KEY_W == keycode || KEY_S == keycode  || KEY_ESC == keycode)
		key_hook(keycode, game);
	return (0);
}

void init_game(t_map *map)
{
    t_game *game = calloc(1, sizeof(t_game));
    game->map = *map;
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(game->mlx, WIDTH,
                                   HEIGHT + 20, "cub3D");
   mlx_key_hook(game->mlx_win, key_action, game);
   mlx_loop(game->mlx);

}

t_map *check_init_map(char* path)
{
    t_dataList *data = read_map(path);
    if (!data) {
        error_exit("Error reading map");
    }

    t_map *map = calloc(1, sizeof(t_map));
    if (!map) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    init_map(map, data);
    if (check_walls(map->map))
        error_exit("Error: Empty space exists\n");
    if (check_corners(map->map))
        error_exit("Error: Empty corner exists\n");
    return (map);
}




int main(int ac, char *av[]){
    if (ac != 2)
        error_exit("problems with arguments");
    if (!check_map_name(av[1]))
        error_exit("Can't open file. The format is not supported!");

    init_game(check_init_map(av[1]));
    
    
    
    // print_data_list(data);
    // print_test(map);
   

    
//    init_textures(game);
//    mlx_hook(game->mlx_win, 17, 1L << 0, exit_game, game);
//    mlx_key_hook(game->mlx_win, key_action, game);

//    free(game);
//    free_data_list(data);
//    free_map(map);
//    free(map);


    return (0);
}