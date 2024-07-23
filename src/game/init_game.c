/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:30:01 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/23 16:18:58 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		free_map(map);
		error_exit("Failed to allocate memory for game\n");
	}
	game->map = map;
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

void	init_walls(t_game *game, t_map *map)
{
	int	w;
	int	h;
	int	i;

	i = -1;
	w = 512;
	h = 512;
	game->walls[0].img = mlx_xpm_file_to_image(game->mlx, map->ea, &w, &h);
	game->walls[1].img = mlx_xpm_file_to_image(game->mlx, map->we, &w, &h);
	game->walls[2].img = mlx_xpm_file_to_image(game->mlx, map->so, &w, &h);
	game->walls[3].img = mlx_xpm_file_to_image(game->mlx, map->no, &w, &h);
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
