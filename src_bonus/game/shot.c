/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:14:38 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/04 20:41:25 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	calculate_max_beam_length(int map_width, int map_height)
{
	return (sqrt(map_width * map_width + map_height * map_height));
}

bool is_collision(t_game *game, int beam_x, int beam_y) {
    // Преобразуем координаты луча в координаты карты
    int map_x = beam_x / TILE_SIZE;
    int map_y = beam_y / TILE_SIZE;

    // Проверка границ карты
    if (map_x < 0 || map_x >= game->map->width || map_y < 0 || map_y >= game->map->height) {
        return true; // Луч вышел за пределы карты, считаем это столкновением
    }

    // Проверка клетки карты на наличие препятствия
    if (game->map[map_x][map_y] == WALL_TILE) {
        return true; // Столкновение с препятствием
    }

    return false; 
}

void	start_shot(t_game *game)
{
	game->shot.is_firing = 1;
	game->shot.beam_length = 0;
	game->shot.beam_speed = 10; // Установить скорость луча
	game->shot.start_x = game->player.pos_x;
	game->shot.start_y = game->player.pos_y;
	// Установить начальную конечную позицию выстрела (например,направление перед игроком)
	game->shot.end_x = game->player.pos_x;
	game->shot.end_y = game->player.pos_y;
	game->shot.max_beam_length = calculate_max_beam_length(game->map->width,
			game->map->height);
}

void	update_shot(t_game *game)
{
	if (game->shot.is_firing)
	{
		// Обновить длину луча
		game->shot.beam_length += game->shot.beam_speed;
		// Обновить конечную позицию луча
		game->shot.end_x = game->shot.start_x + (int)(game->shot.beam_length
				* cos(game->player.dir_x));
		game->shot.end_y = game->shot.start_y + (int)(game->shot.beam_length
				* sin(game->player.dir_y));
		// Проверка на достижение максимальной длины или попадания в препятствие
		if (game->shot.beam_length >= game->shot.max_beam_length
			|| is_collision(game, game->shot.end_x, game->shot.end_y))
		{
			game->shot.is_firing = 0; // Останавливаем выстрел
		}
	}
}

void	draw_shot(t_game *game)
{
	if (game->beam.is_firing)
	{
		int x = game->beam.start_x;
		int y = game->beam.start_y;
		int end_x = game->beam.end_x;
		int end_y = game->beam.end_y;

		// Алгоритм Брезенхема для рисования линии
		int dx = abs(end_x - x);
		int dy = abs(end_y - y);
		int sx = x < end_x ? 1 : -1;
		int sy = y < end_y ? 1 : -1;
		int err = dx - dy;

		while (1)
		{
			// Рисуем пиксель луча
			my_mlx_pixel_put(game->back, x, y, 0xFFFFFF); // Цвет белый,
				можно изменить

			// Если достигли конца луча, выходим из цикла
			if (x == end_x && y == end_y)
				break ;

			int e2 = err * 2;
			if (e2 > -dy)
			{
				err -= dy;
				x += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				y += sy;
			}
		}
	}
}