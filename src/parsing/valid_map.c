/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:14:10 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/27 12:32:54 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	check_walls(char **map);
static bool	check_corners(char **map);

void	check_valid_map(t_map *map)
{
	valid_symbols(map);
	if (check_walls(map->map))
		error_exit_map("Invalid wall structure or internal spaces", map);
	if (check_corners(map->map))
		error_exit_map("Empty corners found. '0' must be surrounded by walls",
			map);
}

// Проверка границ карты
// Проверка наличия достаточной длины строк
// Проверка окружения символа на наличие пробелов

// Check map boundaries
// Check if the string is long enough
// Check character surroundings for spaces
static bool	is_wall_error(char **map, int x, int y)
{
	if (y - 1 < 0 || x - 1 < 0 || !map[y - 1] || !map[y + 1])
	{
		return (true);
	}
	if ((int)ft_strlen(map[y - 1]) <= x || (int)ft_strlen(map[y + 1]) <= x || x
		- 1 < 0 || x + 1 >= (int)ft_strlen(map[y]))
	{
		return (true);
	}
	if (map[y][x + 1] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' '
		|| map[y - 1][x] == ' ')
	{
		return (true);
	}
	return (false);
}

static bool	check_walls(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] == '0' || valid_symbol_character(map[y][x]))
				&& is_wall_error(map, x, y))
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

static bool	check_corners(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || valid_symbol_character(map[y][x]))
			{
				if (!map[y - 1][x + 1] || !map[y + 1][x + 1] || map[y - 1][x
					- 1] == ' ' || map[y + 1][x - 1] == ' ' || map[y - 1][x
					+ 1] == ' ' || map[y + 1][x + 1] == ' ')
					return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}
