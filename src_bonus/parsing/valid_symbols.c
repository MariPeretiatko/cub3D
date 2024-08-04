/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:05:36 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/31 18:38:57 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	valid_symbol(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D');
}

bool	valid_symbol_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	valid_door(t_map *map, const char *row, int col, int row_index)
{
	bool	horizontal_walls;
	bool	vertical_walls;

	if (row[col] == 'D')
	{
		if (col == 0)
			error_exit_map("first symbol in the line", map);
		if (row[col + 1] == '\0')
			error_exit_map("last symbol in the line", map);
		if (row_index + 1 == map->height)
			error_exit_map("the door cant be in last line", map);
		horizontal_walls = (row[col - 1] == '1' && row[col + 1] == '1');
		vertical_walls = (map->map[row_index - 1][col] == '1'
				&& map->map[row_index + 1][col] == '1');
		if (!(horizontal_walls || vertical_walls))
			error_exit_map("Door 'D' is not surrounded by walls properly", map);
	}
}

void	check_map_row_door(t_map *map, const char *row, int *player_count,
		int row_index)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (valid_symbol_character(row[col]))
		{
			if (++(*player_count) > 1)
				error_exit_map("The player's position symbol is not correct"
					"the number is incorrect",map);
		}
		if (!valid_symbol(row[col]))
			error_exit_map("Invalid character in the map", map);
		valid_door(map, row, col, row_index);
		col++;
	}
}

void	valid_symbols_door(t_map *map)
{
	int	row;
	int	player_count;

	row = 0;
	player_count = 0;
	while (map->map[row])
	{
		check_map_row_door(map, map->map[row], &player_count, row);
		row++;
	}
	if (player_count == 0)
		error_exit_map("Missing character on the map", map);
}
