/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:49:33 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/09 10:38:19 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	moves_execute(t_game *game);
int get_pixel(t_image *img, int x, int y);

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
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
				game->map->map[i][j] = '0';
				// game->player.pos_x = i + 0.5;
				// game->player.pos_y = j + 0.5;
				game->player.pos_x = i;
				game->player.pos_y = j;
			}
			j++;
		}
		i++;
	}
}

void	add_plane_characters(t_game *game)
{
	char	plane;

	plane = game->player.direction;
	if (plane == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
	}
	else if (plane == 'N')
	{
		game->player.dir_x = 1;
		game->player.plane_y = -0.66;
	}
	else if (plane == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = -0.66;
	}
	else if (plane == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = 0.66;
	}
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
}

int	check_cardinal_directions(t_game *game)
{
	if (game->rc.side == 0)
	{
		if (game->rc.raydir_x > 0)
			return (EAST); // EAST_COLOR восток
		else
			return (WEST); // WEST_COLOR запад
	}
	else
	{
		if (game->rc.raydir_y > 0)
			return (SOUTH); // SOUTH_COLOR юг
		else
			return (NORTH); // NORTH_COLOR север
	}
}

int get_texture_pixel(t_image *texture, int texX, int texY)
{
    // Проверка на наличие текстуры и корректные координаты
    if (!texture || !texture->addr || texX < 0 || texY < 0 || texX >= texture->width || texY >= texture->height) {
        return 0; // Возвращаем нулевой цвет по умолчанию или другое значение по вашему выбору
    }

    // Вычисляем смещение до нужного пикселя в адресе данных текстуры
    int offset = texY * (texture->line_length / (texture->bits_per_pixel / 8)) + texX;

    // Приводим указатель к нужному типу (unsigned int*), чтобы получить цвет пикселя
    unsigned int *pixel = (unsigned int *)(texture->addr + offset * (texture->bits_per_pixel / 8));

    // Возвращаем значение цвета пикселя
    return *pixel;
}

int	render(t_game *game)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	draw_floor_and_ceiling(game);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		game->rc.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		game->rc.raydir_x = game->player.dir_x + game->player.plane_x
			* game->rc.camera_x;
		game->rc.raydir_y = game->player.dir_y + game->player.plane_y
			* game->rc.camera_x;
		game->rc.map_x = (int)game->player.pos_x;
		game->rc.map_y = (int)game->player.pos_y;
		game->rc.delta_dist_x = fabs(1 / game->rc.raydir_x);
		game->rc.delta_dist_y = fabs(1 / game->rc.raydir_y);
		if (game->rc.raydir_x < 0)
		{
			game->rc.step_x = -1;
			game->rc.side_dist_x = (game->player.pos_x - game->rc.map_x)
				* game->rc.delta_dist_x;
		}
		else
		{
			game->rc.step_x = 1;
			game->rc.side_dist_x = (game->rc.map_x + 1.0 - game->player.pos_x)
				* game->rc.delta_dist_x;
		}
		if (game->rc.raydir_y < 0)
		{
			game->rc.step_y = -1;
			game->rc.side_dist_y = (game->player.pos_y - game->rc.map_y)
				* game->rc.delta_dist_y;
		}
		else
		{
			game->rc.step_y = 1;
			game->rc.side_dist_y = (game->rc.map_y + 1.0 - game->player.pos_y)
				* game->rc.delta_dist_y;
		}
		game->rc.hit = 0;
		while (game->rc.hit == 0)
		{
			if (game->rc.side_dist_x < game->rc.side_dist_y)
			{
				game->rc.side_dist_x += game->rc.delta_dist_x;
				game->rc.map_x += game->rc.step_x;
				game->rc.side = 0;
			}
			else
			{
				game->rc.side_dist_y += game->rc.delta_dist_y;
				game->rc.map_y += game->rc.step_y;
				game->rc.side = 1;
			}
			if (game->map->map[game->rc.map_x][game->rc.map_y] > '0')
				game->rc.hit = 1;
		}
		if (game->rc.side == 0)
			game->rc.perp_wall_dist = (game->rc.map_x - game->player.pos_x + (1
						- game->rc.step_x) / 2) / game->rc.raydir_x + 0.0001;
		else
			game->rc.perp_wall_dist = (game->rc.map_y - game->player.pos_y + (1
						- game->rc.step_y) / 2) / game->rc.raydir_y + 0.0001;
		// line_height = (int)(SCREEN_HEIGHT / game->rc.perp_wall_dist);
		// draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		// if (draw_start < 0)
		// 	draw_start = 0;
		// draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		// if (draw_end >= SCREEN_HEIGHT)
		// 	draw_end = SCREEN_HEIGHT - 1;
		line_height = (int)(SCREEN_HEIGHT / game->rc.perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		// if (game->rc.side == 0)
		// {
		// 	if (game->rc.raydir_x > 0)
		// 		color = PINK; // EAST_COLOR восток
		// 	else
		// 		color = GREEN; // WEST_COLOR запад
		// }
		// else
		// {
		// 	if (game->rc.raydir_y > 0)
		// 		color = RED; // SOUTH_COLOR юг
		// 	else
		// 		color = YELLOW; // NORTH_COLOR север
		// }
		//стены плывут
		// double wallX;
		// if (game->rc.side == 0)
    	// 	wallX = game->player.pos_y + game->rc.perp_wall_dist * game->rc.raydir_y;
		// else
    	// 	wallX = game->player.pos_x + game->rc.perp_wall_dist * game->rc.raydir_x;
		// wallX -= floor(wallX);
		
		// int texX = (int)(wallX * (double)game->walls[0].width);
		// if (game->rc.side == 0 && game->rc.raydir_x > 0)
		//     texX = game->walls[0].width - texX - 1;
		// if (game->rc.side == 1 && game->rc.raydir_y < 0)
		//     texX = game->walls[0].width - texX - 1;
		
		// for (int y = draw_start; y < draw_end; y++) {
		//     double texPos = (y - draw_start) * (double)game->walls[0].height / (draw_end - draw_start);
		//     int texY = (int)texPos & (game->walls[0].height - 1);
		//     color = get_texture_pixel(&game->walls[check_cardinal_directions(game)], texX, texY);
		//     my_mlx_pixel_put(&game->back, x, y, color);
		// }

		double wallX;
		if (game->rc.side == 0)
		    wallX = game->player.pos_y + game->rc.perp_wall_dist * game->rc.raydir_y;
		else
		    wallX = game->player.pos_x + game->rc.perp_wall_dist * game->rc.raydir_x;
		wallX -= floor(wallX);  // Извлечение дробной части для координаты текстуры
		
		int texX = (int)(wallX * (double)game->walls[0].width);
		if (game->rc.side == 0 && game->rc.raydir_x > 0)
		    texX = game->walls[0].width - texX - 1;
		if (game->rc.side == 1 && game->rc.raydir_y < 0)
		    texX = game->walls[0].width - texX - 1;
		
		double step = 1.0 * game->walls[0].height / line_height;
		double texPos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
		
		for (int y = draw_start; y < draw_end; y++) {
		    int texY = (int)texPos & (game->walls[0].height - 1);
		    texPos += step;
		    color = get_texture_pixel(&game->walls[check_cardinal_directions(game)], texX, texY);
		    my_mlx_pixel_put(&game->back, x, y, color);
		}
		
		// for (int y = draw_start; y < draw_end; y++)
		// {
		// 	// my_mlx_pixel_put(&game->back, x, y, color);


		// 	my_mlx_pixel_put(&game->back, x, y, color = get_pixel(&game->walls[check_cardinal_directions(game)], x, y));
		// }
	}
	moves_execute(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->back.img, 0, 0);
	return (0);
}

void	move_front(t_game *game)
{
	if (game->map->map[(int)(game->player.pos_x + game->player.dir_x
			* MOVE_SPEED)][(int)game->player.pos_y] == '0')
		game->player.pos_x += game->player.dir_x * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos_x][(int)(game->player.pos_y
			+ game->player.dir_y * MOVE_SPEED)] == '0')
		game->player.pos_y += game->player.dir_y * MOVE_SPEED;
}

void	move_back(t_game *game)
{
	if (game->map->map[(int)(game->player.pos_x - game->player.dir_x
			* MOVE_SPEED)][(int)game->player.pos_y] == '0')
		game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos_x][(int)(game->player.pos_y
			- game->player.dir_y * MOVE_SPEED)] == '0')
		game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROTATION_SPEED)
		- game->player.dir_y * sin(-ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) + game->player.dir_y
		* cos(-ROTATION_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-ROTATION_SPEED)
		- game->player.plane_y * sin(-ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player.plane_y * cos(-ROTATION_SPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED)
		- game->player.dir_y * sin(ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir_y
		* cos(ROTATION_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED)
		- game->player.plane_y * sin(ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(ROTATION_SPEED)
		+ game->player.plane_y * cos(ROTATION_SPEED);
}

void	move_left(t_game *game)
{
	if (game->map->map[(int)(game->player.pos_x - game->player.plane_x
			* MOVE_SPEED)][(int)game->player.pos_y] == '0')
		game->player.pos_x -= game->player.plane_x * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos_x][(int)(game->player.pos_y
			- game->player.plane_y * MOVE_SPEED)] == '0')
		game->player.pos_y -= game->player.plane_y * MOVE_SPEED;
}

void	move_right(t_game *game)
{
	if (game->map->map[(int)(game->player.pos_x + game->player.plane_x
			* MOVE_SPEED)][(int)game->player.pos_y] == '0')
		game->player.pos_x += game->player.plane_x * MOVE_SPEED;
	if (game->map->map[(int)game->player.pos_x][(int)(game->player.pos_y
			+ game->player.plane_y * MOVE_SPEED)] == '0')
		game->player.pos_y += game->player.plane_y * MOVE_SPEED;
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
	{
		write(1, "\nKEY_W\n", 7);
		game->pressed.W = true;
	}
	if (keycode == KEY_S)
	{
		write(1, "\nKEY_S\n", 7);
		game->pressed.S = true;
	}
	if (keycode == KEY_A)
	{
		write(1, "\nKEY_A\n", 7);
		game->pressed.A = true;
	}
	if (keycode == KEY_D)
	{
		write(1, "\nKEY_D\n", 7);
		game->pressed.D = true;
	}
	if (keycode == KEY_RIGHT)
	{
		write(1, "\nKEY_RIGHT\n", 11);
		game->pressed.right = true;
	}
	if (keycode == KEY_LEFT)
	{
		write(1, "\nKEY_LEFT\n", 10);
		game->pressed.left = true;
	}
	return (0);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W && game->pressed.W)
		game->pressed.W = false;
	if (keycode == KEY_S && game->pressed.S)
		game->pressed.S = false;
	if (keycode == KEY_A && game->pressed.A)
		game->pressed.A = false;
	if (keycode == KEY_D && game->pressed.D)
		game->pressed.D = false;
	if (keycode == KEY_LEFT && game->pressed.left)
		game->pressed.left = false;
	if (keycode == KEY_RIGHT && game->pressed.right)
		game->pressed.right = false;
	printf("key_release_hook\n");
	return (0);
}

bool	moves_execute(t_game *game)
{
	if (game->pressed.W)
		move_front(game);
	if (game->pressed.S)
		move_back(game);
	if (game->pressed.A)
		move_left(game);
	if (game->pressed.D)
		move_right(game);
	if (game->pressed.left)
		rotate_left(game);
	if (game->pressed.right)
		rotate_right(game);
	return (true);
}

int	key_action(int keycode, t_game *game)
{
	if (KEY_A == keycode || KEY_LEFT == keycode || KEY_D == keycode
		|| KEY_RIGHT == keycode || KEY_W == keycode || KEY_S == keycode
		|| KEY_ESC == keycode)
		key_hook(keycode, game);
	return (0);
}

int get_pixel(t_image *img, int x, int y)
{
    char *pixel;
    int color;

    pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    if (img->endian == 0)
        color = *(unsigned int *)pixel;
    else
        color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

    return color;
}

void init_walls(t_game *game, t_map *map)
{
	// int Width = 64; 
	// int Height = 64;
	int Width = 512; 
	int Height = 512;
	game->walls[0].height = 512;
	game->walls[0].width = 512;
	game->walls[1].height = 512;
	game->walls[1].width = 512;
	game->walls[2].height = 512;
	game->walls[2].width = 512;
	game->walls[3].height = 512;
	game->walls[3].width = 512;
	
	// game->walls[0].img = malloc(sizeof(t_image));
	// game->walls[1].img = malloc(sizeof(t_image));
	// game->walls[2].img = malloc(sizeof(t_image));
	// game->walls[3].img = malloc(sizeof(t_image));
	
	game->walls[0].img = mlx_xpm_file_to_image(game->mlx, map->EA, &Width, &Height);
	game->walls[1].img = mlx_xpm_file_to_image(game->mlx, map->WE, &Width, &Height);
	game->walls[2].img = mlx_xpm_file_to_image(game->mlx, map->SO, &Width, &Height);
	game->walls[3].img = mlx_xpm_file_to_image(game->mlx, map->NO, &Width, &Height);
	
	game->walls[0].addr = mlx_get_data_addr(game->walls[0].img,
			&game->walls[0].bits_per_pixel, &game->walls[0].line_length, &game->walls[0].endian);
	game->walls[1].addr = mlx_get_data_addr(game->walls[1].img,
			&game->walls[1].bits_per_pixel, &game->walls[1].line_length, &game->walls[1].endian);
	game->walls[2].addr = mlx_get_data_addr(game->walls[2].img,
			&game->walls[2].bits_per_pixel, &game->walls[2].line_length, &game->walls[2].endian);
	game->walls[3].addr = mlx_get_data_addr(game->walls[3].img,
			&game->walls[3].bits_per_pixel, &game->walls[3].line_length, &game->walls[3].endian);
	if (!game->walls[0].img || !game->walls[1].img || !game->walls[2].img || !game->walls[3].img)
		error_exit("textures");

	printf("%d\n", game->walls[0].bits_per_pixel);
	printf("%d\n", game->walls[0].line_length);
	printf("%d\n", game->walls[1].line_length);
	printf("%d\n", game->walls[2].line_length);
	// game->back.addr = mlx_get_data_addr(game->back.img,
	// 		&game->back.bits_per_pixel, &game->back.line_length,
	// 		&game->back.endian);
	
}

void	init_game(t_map *map)
{
	t_game	*game;

	game = calloc(1, sizeof(t_game));
	if (!game)
	{
		fprintf(stderr, "Failed to allocate memory for game\n");
		exit(1);
	}
	game->map = map;
	if (!game->map)
	{
		fprintf(stderr, "Map is null\n");
		free(game);
		exit(1);
	}
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3D");
	game->back.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->back.addr = mlx_get_data_addr(game->back.img,
			&game->back.bits_per_pixel, &game->back.line_length,
			&game->back.endian);
	init_walls(game, game->map);
	init_position_charactor(game);
	add_plane_characters(game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->mlx_win, KEY_PRESS, KEY_PRESS_MASK, key_action, game);
	mlx_hook(game->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook,
		game);
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