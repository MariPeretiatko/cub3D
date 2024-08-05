/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:07:28 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/05 23:03:52 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	is_inside_minimap_circle(int x, int y, int radius)
{
	int	dx;
	int	dy;

	dx = x - radius;
	dy = y - radius;
	return (dx * dx + dy * dy <= radius * radius);
}

static void	draw_minimap_bg_circle(int radius, t_image *bg, int bg_color)
{
	int	x;
	int	y;
	int	minimap_diameter;

	y = -1;
	minimap_diameter = radius * 2;
	while (++y < minimap_diameter)
	{
		x = -1;
		while (++x < minimap_diameter)
		{
			if (is_inside_minimap_circle(x, y, radius))
				my_mlx_pixel_put(bg, MAP_OFFSET + x, MAP_OFFSET + y, bg_color);
		}
	}
}

static void	draw_minimap_wall_pixel(int wall_x, int wall_y, t_image *bg,
		int bg_color)
{
	int	x;
	int	y;
	int	pixel_x;
	int	pixel_y;

	y = -1;
	while (++y < MINI_CUBE)
	{
		x = -1;
		while (++x < MINI_CUBE)
		{
			pixel_x = MAP_RADIUS + wall_x + x;
			pixel_y = MAP_RADIUS + wall_y + y;
			if (is_inside_minimap_circle(pixel_x, pixel_y, MAP_RADIUS))
				my_mlx_pixel_put(bg, pixel_x + MAP_OFFSET, pixel_y + MAP_OFFSET,
					bg_color);
		}
	}
}

static void	draw_minimap_player(t_image *bg)
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			if (x * x + y * y <= 3 * 3)
			{
				my_mlx_pixel_put(bg, MAP_OFFSET + MAP_RADIUS + x, MAP_OFFSET
					+ MAP_RADIUS + y, 0xFF0000);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game, t_map *map, t_player *player)
{
	int	wall_x;
	int	wall_y;

	draw_minimap_bg_circle(MAP_RADIUS, game->back, 0x06343d);
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (map->map[i][j] == '1' || map->map[i][j] == 'D'
				|| map->map[i][j] == 'O')
			{
				wall_x = (j - player->pos_y) * MINI_CUBE;
				wall_y = (i - player->pos_x) * MINI_CUBE;
				draw_minimap_wall_pixel(wall_x, wall_y, game->back,
					define_color(map->map[i][j]));
			}
		}
	}
	draw_minimap_player(game->back);
}
