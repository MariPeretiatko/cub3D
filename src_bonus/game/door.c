/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:59:11 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/05 17:48:56 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	toggle_door(t_game *game, int x, int y)
{
	double	distance;

	distance = calculate_distance(game->player.pos_x, game->player.pos_y, x, y);
	if (distance < 2)
	{
		game->door_x = x;
		game->door_y = y;
		if (game->map->map[x][y] == 'D')
		{
			game->door_open = 1;
		}
		else if (game->map->map[x][y] == 'O')
		{
			game->door_open = false;
		}
	}
}

void	update_status_door(t_game *game)
{
	int	door_x;
	int	door_y;

	door_x = game->door_x;
	door_y = game->door_y;
	if (game->door_open)
	{
		if (game->map->map[door_x][door_y] == 'D')
			game->map->map[door_x][door_y] = 'O';
	}
	else
	{
		if (game->map->map[door_x][door_y] == 'O')
			game->map->map[door_x][door_y] = 'D';
	}
}

void	render_door(t_game *game, int x, int y)
{
	int	texture_x;
	int	texture_y;
	int	color;

	texture_x = (int)(game->rc.wall_x * TEXWIDTH);
	texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
	game->rc.tex_pos += game->rc.step;
	color = get_texture_pixel(game->door, texture_x, texture_y);
	my_mlx_pixel_put(game->back, x, y, color);
}
