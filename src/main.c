#include "../inc/cub3d.h"


void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



void	init_position_charactor(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (valid_symbol_character(game->map->map[i][j]))
			{
				game->player.direction = game->map->map[i][j];
				game->player.pos_x = j;
				game->player.pos_y = i;
				// game->player.pos_x = j - 0.5;
				// game->player.pos_y = i - 0.5;
			}
			j++;
		}
		i++;
	}
}

void load_textures(t_game *game);

void add_plane_characters(t_game *game)
{
	// char plane = game->player.direction;
	game->player.dir_x = -1;
    game->player.dir_y = 0;
    game->player.plane_x = 0;
    game->player.plane_y = 0.66;
	// if(plane == 'S')
	// {
	// 	game->player.dir_x = -1;
	// 	game->player.dir_y = 0;
	// 	game->player.plane_x = 0;
	// 	game->player.plane_y = 0.66;
	// }
	// else if(plane == 'N')
	// {
	// 	game->player.plane_y = -1;
	// 	game->player.dir_x = -0.66;
	// }
	// else if(plane == 'E')
	// {
	// 	game->player.dir_x = 1;
	// 	game->player.plane_y = -0.66;
	// }
	// else if(plane == 'S')
	// {
	// 	game->player.dir_y = 1;
	// 	game->player.plane_x = 0.66;
	// }
}

void	draw_floor_and_ceiling(t_game *game)
{
	unsigned int	*dst;
	int				i;
	dst = (unsigned int *)game->back.addr;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_ceiling;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_floor;
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->back.img, 0, 0);
}


void render(t_game *game) {
    draw_floor_and_ceiling(game);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        game->rc.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        game->rc.raydir_x = game->player.dir_x + game->player.plane_x * game->rc.camera_x;
        game->rc.raydir_y = game->player.dir_y + game->player.plane_y * game->rc.camera_x;

        game->rc.map_x = (int)game->player.pos_x;
        game->rc.map_y = (int)game->player.pos_y;

        game->rc.delta_dist_x = fabs(1 / game->rc.raydir_x);
        game->rc.delta_dist_y = fabs(1 / game->rc.raydir_y);
        // data->raycast.perp_wall_dist;

        if (game->rc.raydir_x < 0) {
            game->rc.step_x = -1;
            game->rc.side_dist_x = (game->player.pos_x - game->rc.map_x) * game->rc.delta_dist_x;
        }
        else {
            game->rc.step_x = 1;
            game->rc.side_dist_x = (game->rc.map_x + 1.0 - game->player.pos_x) * game->rc.delta_dist_x;
        }
        if (game->rc.raydir_y < 0) {
            game->rc.step_y = -1;
            game->rc.side_dist_y = (game->player.pos_y - game->rc.map_y) * game->rc.delta_dist_y;
        }
        else {
            game->rc.step_y = 1;
            game->rc.side_dist_y = (game->rc.map_y + 1.0 - game->player.pos_y) * game->rc.delta_dist_y;
        }

        game->rc.hit = 0;
        // data->raycast.side;

        while (game->rc.hit == 0) {
            if (game->rc.side_dist_x < game->rc.side_dist_y) {
                game->rc.side_dist_x += game->rc.delta_dist_x;
                game->rc.map_x += game->rc.step_x;
                game->rc.side = 0;
            }
            else {
                game->rc.side_dist_y += game->rc.delta_dist_y;
                game->rc.map_y += game->rc.step_y;
                game->rc.side = 1;
            }
            if (game->map->map[game->rc.map_x][game->rc.map_y] > 0)
                game->rc.hit = 1;
        }

        if (game->rc.side == 0)
            game->rc.perp_wall_dist = (game->rc.map_x - game->player.pos_x + (1 - game->rc.step_x) / 2) / game->rc.raydir_x;
        else
            game->rc.perp_wall_dist = (game->rc.map_y - game->player.pos_y + (1 - game->rc.step_y) / 2) / game->rc.raydir_y;

        int lineHeight = (int)(SCREEN_HEIGHT / game->rc.perp_wall_dist);

        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        int color = (game->rc.side == 1) ? RED : BLUE;

        for (int y = drawStart; y < drawEnd; y++) {
            my_mlx_pixel_put(&game->back, x, y, color);
        }
    }

    // mlx_put_image_to_window(game->mlx, game->mlx_win, game->back.img, 0, 0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
        exit(0);
    // double moveSpeed = 0.3;
    // double rotSpeed = 0.2;
    if (keycode == KEY_W) { 
        game->pressed.W = true;
        if(game->map->map[(int)(game->player.pos_x + game->player.dir_x * MOVE_SPEED)][(int)game->player.pos_y] == 0) 
			game->player.pos_x += game->player.dir_x * MOVE_SPEED;
        if(game->map->map[(int)game->player.pos_x][(int)(game->player.pos_y + game->player.dir_y * MOVE_SPEED)] == 0) 
			game->player.pos_y += game->player.pos_y * MOVE_SPEED;
    }
    if (keycode == KEY_S) {
        game->pressed.S = true;
        if(game->map->map[(int)(game->player.pos_x - game->player.dir_x* MOVE_SPEED)][(int)game->player.pos_y] == 0) 
			game->player.pos_x -= game->player.pos_x * MOVE_SPEED;
        if(game->map->map[(int)game->player.pos_x][(int)(game->player.pos_y - game->player.dir_y * MOVE_SPEED)] == 0) 
			game->player.pos_y -= game->player.pos_y * MOVE_SPEED;
    }
    if (keycode == KEY_RIGHT) { // Right arrow
        game->pressed.right = true;
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROTATION_SPEED) - game->player.dir_y * sin(-ROTATION_SPEED);
        game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) + game->player.dir_y * cos(-ROTATION_SPEED);
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROTATION_SPEED) - game->player.plane_y * sin(-ROTATION_SPEED);
        game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED) + game->player.plane_y * cos(-ROTATION_SPEED);
    }
    if (keycode == KEY_LEFT) { // Left arrow
        game->pressed.left = true;
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED) - game->player.dir_y * sin(ROTATION_SPEED);
        game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir_y * cos(ROTATION_SPEED);
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED) - game->player.dir_y * sin(ROTATION_SPEED);
        game->player.dir_y = old_plane_x * sin(ROTATION_SPEED) + game->player.dir_y * cos(ROTATION_SPEED);
    }
    mlx_clear_window(game->mlx, game->mlx_win);
    render(game);
    return (0);
}

int	key_action(int keycode, t_game *game)
{
	if (KEY_A == keycode || KEY_LEFT == keycode || KEY_D == keycode
		|| KEY_RIGHT == keycode || KEY_W == keycode || KEY_S == keycode
		|| KEY_ESC == keycode)
		key_hook(keycode, game);
	return (0);
}

// int main_show(t_game *game)
// {

// 	ceiling_floor(game);
// 	// init_raycast(game);
// 	// keys_execute(game);
// 	mlx_put_image_to_window(game->mlx, game->mlx_win, game->back.img, 0, 0);
// 	return (0);
// }

int key_release_hook(int keycode, t_game *game){
    if (keycode == KEY_W && game->pressed.W)
        game->pressed.W = false;
    if(keycode == KEY_S && game->pressed.S)
        game->pressed.S = false;
    if(keycode == KEY_LEFT && game->pressed.left)
        game->pressed.left = false;
    if(keycode == KEY_RIGHT && game->pressed.right)
        game->pressed.right = false;
    return (0);
}

void	init_game(t_map *map)
{
	t_game	*game;

	game = calloc(1, sizeof(t_game));
	game->map = map;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT + 20, "cub3D");
	game->back.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->back.addr = mlx_get_data_addr(game->back.img,
			&game->back.bits_per_pixel,
			&game->back.line_length, &game->back.endian);
	// print_map_game(game, map);
	init_position_charactor(game);
	add_plane_characters(game);
	render(game);

    mlx_hook(game->mlx_win, KEY_PRESS, KEY_PRESS_MASK, key_action, &game);
    mlx_hook(game->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, &game);
	// mlx_loop_hook(game->mlx, main_show, game);
	// // init_raycast(game);
	// mlx_key_hook(game->mlx_win, key_action, game);
	mlx_loop(game->mlx);
}

t_map	*check_init_map(char *path)
{
	t_dataList	*data;
	t_map		*map;

	data = read_map(path);
	if (!data)
	{
		error_exit("Error reading map");
	}
	map = calloc(1, sizeof(t_map));
	if (!map)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	init_map(map, data);
	valid_symbols(map->map);
	if (check_walls(map->map))
		error_exit("Error: Empty space exists\n");
	if (check_corners(map->map))
		error_exit("Error: Empty corner exists\n");
	// print_data_list(data);
	// print_test(map);
	return (map);
}



int	main(int ac, char *av[])
{
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