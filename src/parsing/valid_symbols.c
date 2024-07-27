/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:05:36 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/27 00:55:45 by mperetia         ###   ########.fr       */
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

void	check_map_row(t_map *map, const char *row, int *player_count)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (valid_symbol_character(row[col]))
		{
			if (++(*player_count) > 1)
				error_exit_map("The player's position symbol is not correct"
					"the number is incorrect", map);
		}
		if (!valid_symbol(row[col]))
			error_exit_map("Invalid character in the map", map);
		col++;
	}
}

void	valid_symbols(t_map *map)
{
	int	row;
	int	player_count;

	row = 0;
	player_count = 0;
	while (map->map[row])
	{
		check_map_row(map, map->map[row], &player_count);
		row++;
	}
	if (player_count == 0)
		error_exit_map("Missing character on the map", map);
}
