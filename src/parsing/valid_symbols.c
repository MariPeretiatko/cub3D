/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:05:36 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/22 13:38:07 by mperetia         ###   ########.fr       */
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
					error_exit("The player's position symbol is not correct,"
						"the number is incorrect");
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
