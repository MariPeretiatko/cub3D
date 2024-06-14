/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:14:10 by mperetia          #+#    #+#             */
/*   Updated: 2024/06/15 00:01:34 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	valid_symbol(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

bool	valid_symbol_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	valid_symbols(char **map)
{
	int	row;
	int	col;
	int	player_count;

	row = 0;
	player_count = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (valid_symbol_character(map[row][col]))
			{
				if (++player_count > 1)
					error_exit("The player's position symbol is not correct,the number is incorrect");
			}
			if (!valid_symbol(map[row][col]))
				error_exit("Invalid character in the map");
			col++;
		}
		row++;
	}
	if (player_count == 0)
		error_exit("Missing character on the map");
}

bool	is_wall_error(char **map, int x, int y)
{
	if (y - 1 < 0 || x - 1 < 0 || !map[y - 1] || !map[y + 1]
		|| (int)strlen(map[y - 1]) <= x || (int)strlen(map[y + 1]) <= x || !map[y][x - 1]
		|| !map[y][x + 1] || map[y][x + 1] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y - 1][x] == ' ')
	{
		return (true);
	}
	return (false);
}

bool	check_walls(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (valid_symbol_character(map[y][x]) && is_wall_error(map, x, y))
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

bool	check_corners(char **map)
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
				{
					return (true);
				}
			}
			x++;
		}
		y++;
	}
	return (false);
}
