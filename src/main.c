/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:49:33 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/10 19:22:10 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	moves_execute(t_game *game);
int		get_pixel(t_image *img, int x, int y);

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
				game->player.pos_x = i + 0.5;
				game->player.pos_y = j + 0.5;
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
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (game->rc.raydir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}
int	get_pixel(t_image *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	if (img->endian == 0)
		color = *(unsigned int *)pixel;
	else
		color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	return (color);
}
//123
int	get_texture_pixel(t_image *texture, int texX, int texY)
{
	int				offset;
	unsigned int	*pixel;

	if (!texture || !texture->addr || texX < 0 || texY < 0
		|| texX >= texture->width || texY >= texture->height)
		return (0);
	offset = texY * (texture->line_length / (texture->bits_per_pixel / 8))
		+ texX;
	pixel = (unsigned int *)(texture->addr + offset * (texture->bits_per_pixel
				/ 8));
	return (*pixel);
}

void	ray_direction_calculate(t_game *game, int x)
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
}

void	calculate_step_and_dist(t_game *game)
{
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
}

void	set_ray_steps(t_game *game)
{
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
}

void	calculate_wall_parameters(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.perp_wall_dist = (game->rc.map_x - game->player.pos_x + (1
					- game->rc.step_x) / 2) / game->rc.raydir_x + 0.0001;
	else
		game->rc.perp_wall_dist = (game->rc.map_y - game->player.pos_y + (1
					- game->rc.step_y) / 2) / game->rc.raydir_y + 0.0001;
	game->rc.line_height = (int)(SCREEN_HEIGHT / game->rc.perp_wall_dist);
	game->rc.draw_start = -game->rc.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->rc.draw_start < 0)
		game->rc.draw_start = 0;
	game->rc.draw_end = game->rc.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->rc.draw_end >= SCREEN_HEIGHT)
		game->rc.draw_end = SCREEN_HEIGHT - 1;
}

void	calculate_texture_coordinates(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.wallX = game->player.pos_y + game->rc.perp_wall_dist
			* game->rc.raydir_y;
	else
		game->rc.wallX = game->player.pos_x + game->rc.perp_wall_dist
			* game->rc.raydir_x;
	game->rc.wallX -= floor(game->rc.wallX);
	game->rc.texX = (int)(game->rc.wallX * (double)game->walls[0].width);
	if (game->rc.side == 0 && game->rc.raydir_x > 0)
		game->rc.texX = game->walls[0].width - game->rc.texX - 1;
	if (game->rc.side == 1 && game->rc.raydir_y < 0)
		game->rc.texX = game->walls[0].width - game->rc.texX - 1;
	game->rc.step = 1.0 * game->walls[0].height / game->rc.line_height;
	game->rc.texPos = (game->rc.draw_start - SCREEN_HEIGHT / 2
			+ game->rc.line_height / 2) * game->rc.step;
}

void	render_walls(t_game *game, int x, int y)
{
	game->rc.texY = (int)game->rc.texPos & (game->walls[0].height - 1);
	game->rc.texPos += game->rc.step;
	game->rc.color = get_texture_pixel(&game->walls[check_cardinal_directions(game)],
			game->rc.texX, game->rc.texY);
	my_mlx_pixel_put(&game->back, x, y, game->rc.color);
}

int	render(t_game *game)
{
	int	y;

	draw_floor_and_ceiling(game);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			render_walls(game, x, y);
		}
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
		game->pressed.W = true;
	if (keycode == KEY_S)
		game->pressed.S = true;
	if (keycode == KEY_A)
		game->pressed.A = true;
	if (keycode == KEY_D)
		game->pressed.D = true;
	if (keycode == KEY_RIGHT)
		game->pressed.right = true;
	if (keycode == KEY_LEFT)
		game->pressed.left = true;
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



void	init_walls(t_game *game, t_map *map)
{
	int	w;
	int	h;
	int	i;

	i = -1;
	w = 512;
	h = 512;
	game->walls[0].img = mlx_xpm_file_to_image(game->mlx, map->EA, &w, &h);
	game->walls[1].img = mlx_xpm_file_to_image(game->mlx, map->WE, &w, &h);
	game->walls[2].img = mlx_xpm_file_to_image(game->mlx, map->SO, &w, &h);
	game->walls[3].img = mlx_xpm_file_to_image(game->mlx, map->NO, &w, &h);
	if (!game->walls[0].img || !game->walls[1].img || !game->walls[2].img
		|| !game->walls[3].img)
		error_exit("textures");
	while (++i < 4)
	{
		game->walls[i].addr = mlx_get_data_addr(game->walls[i].img,
				&game->walls[i].bits_per_pixel, &game->walls[i].line_length,
				&game->walls[i].endian);
		game->walls[i].height = 512;
		game->walls[i].width = 512;
	}
}

void	init_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
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
	map = ft_calloc(1, sizeof(t_map));
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