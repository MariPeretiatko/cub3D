/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:30:01 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/26 16:01:26 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_mlx_window(t_game *game);
void	init_background(t_game *game);
void	init_position_charactor(t_game *game);
int		exit_game(t_game *game);

void	init_game(t_map *map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		error_exit_map("Failed to allocate memory for game", map);
	game->map = map;
	init_mlx_window(game);
	init_walls(game);
	init_background(game);
	init_position_charactor(game);
	add_plane_characters(game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->mlx_win, KEY_PRESS, KEY_PRESS_MASK, key_action, game);
	mlx_hook(game->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook,
		game);
	mlx_hook(game->mlx_win, 17, 1L << 0, exit_game, game);
	mlx_loop(game->mlx);
}

void	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit_game("Failed to initialize mlx", game);
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3D");
	if (!game->mlx_win)
		error_exit_game("Failed to create mlx window", game);
}

void	init_background(t_game *game)
{
	game->back = malloc(sizeof(t_image));
	if (!game->back)
		error_exit_game("Failed to allocate memory for background", game);
	game->back->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->back->img)
		error_exit_game("Failed to create background image", game);
	game->back->addr = mlx_get_data_addr(game->back->img,
			&game->back->bits_per_pixel, &game->back->line_length,
			&game->back->endian);
	if (!game->back->addr)
		error_exit_game("Failed to get background image address", game);
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

int	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
