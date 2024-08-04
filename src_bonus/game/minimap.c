/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:07:28 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/04 22:11:26 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_circle(t_game *game, int x, int y, int radius)
{
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				my_mlx_pixel_put(game->back, x + dx, y + dy, GREEN);
			}
		}
	}
}

void	draw_minimap(t_game *game, t_map *map, t_player *player)
{
	int		minimap_diameter;
	int		minimap_left;
	int		minimap_top;
	int		background_color;
	int		dx;
	int		dy;
	double	wall_x;
	double	wall_y;
	int		screen_x;
	int		screen_y;
	int		pixel_x;
	int		pixel_y;

	int cell_size = 15;       // Size of each cell in the minimap
	int minimap_radius = 100; // Radius of the minimap
	int minimap_x = 75;       // X position for minimap (bottom left corner)
	int minimap_y = 75;       // Y position for minimap (bottom left corner)
	minimap_diameter = minimap_radius * 2;
	minimap_left = minimap_x;
	minimap_top = minimap_y;
	//bg color for minimap
	background_color = 0x06343d;
	// background_color = 0x1a2f33;
	// background_color = 0x243336;
	// Draw the green background of the minimap
	for (int y = 0; y < minimap_diameter; y++)
	{
		for (int x = 0; x < minimap_diameter; x++)
		{
			dx = x - minimap_radius;
			dy = y - minimap_radius;
			if (dx * dx + dy * dy <= minimap_radius * minimap_radius)
			{ // Within circle
				my_mlx_pixel_put(game->back, minimap_left + x, minimap_top + y,
					background_color);
			}
		}
	}
	// Draw walls on the minimap
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (map->map[i][j] == '1' || map->map[i][j] == 'D'
				|| map->map[i][j] == 'O')
			{ // Walls, dors
				// bg color for dors, walls
				if (map->map[i][j] == '1')
					background_color = 0x000000;
				else if (map->map[i][j] == 'D')
					background_color = 0x3b2105;
				else if (map->map[i][j] == 'O')
					background_color = 0x3a6616;
				// Calculate the wall's position relative to the player
				wall_x = (j - player->pos_y) * cell_size;
				wall_y = (i - player->pos_x) * cell_size;
				// Translate the coordinates to the minimap position
				screen_x = minimap_left + minimap_radius + (int)wall_x;
				screen_y = minimap_top + minimap_radius + (int)wall_y;
				// Check if any part of the wall falls within the minimap circle
				for (int y = 0; y < cell_size; y++)
				{
					for (int x = 0; x < cell_size; x++)
					{
						pixel_x = screen_x + x;
						pixel_y = screen_y + y;
						// Check if the pixel is within the minimap circle
						dx = pixel_x - (minimap_left + minimap_radius);
						dy = pixel_y - (minimap_top + minimap_radius);
						if (dx * dx + dy * dy <= minimap_radius
							* minimap_radius)
						{
							// Draw the pixel (within the circle)
							my_mlx_pixel_put(game->back, pixel_x, pixel_y,
								background_color);
							// Black color for walls
						}
					}
				}
			}
		}
	}
	// Draw player position
	for (int y = -3; y <= 3; y++)
	{
		for (int x = -3; x <= 3; x++)
		{
			if (x * x + y * y <= 9)
			{ // Circle radius
				my_mlx_pixel_put(game->back, minimap_left + minimap_radius + x,
					minimap_top + minimap_radius + y, 0xFF0000);
			}
		}
	}
}

// void draw_minimap(t_game *game, t_map *map, t_player *player)
// {
// 	int cell_size = 10;
//     int minimap_radius = 50; // радиус миникарты
//     int minimap_x = 75; // позиция X для миникарты (левый нижний угол)
//     int minimap_y = 75; // позиция Y для миникарты (левый нижний угол)

//     // Отрисовка круга для миникарты
//     // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // белый цвет
//     draw_circle(game, minimap_x, minimap_y, minimap_radius);

//     // Отрисовка игрока в центре миникарты
//     // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // красный цвет
//     // SDL_RenderDrawPoint(renderer, minimap_x, minimap_y);

// //  0xFFFFFF
//     // Отрисовка стен на миникарте
//     // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // черный цвет
// 	// printf("map->height = %d\n", map->height);
// 	// printf(" map->width) = %d\n", map->width);
//     for (int i = 0; i < map->height; i++) {
//     for (int j = 0; j < map->width; j++) {
//         if (map->map[i][j] == '1') { // стена
//             int wall_x = minimap_x + (j - player->pos_x) * cell_size;
//             int wall_y = minimap_y + (i - player->pos_y) * cell_size;
//             for (int y = 0; y < cell_size; y++) {
//                 for (int x = 0; x < cell_size; x++) {
//                     my_mlx_pixel_put(game->back, wall_x - cell_size / 2 + x,
// wall_y - cell_size / 2 + y, BLUE);
//                 }
//             }
//         }
//     }
// }

// 	for (int y = -6; y <= 6; y++)
// 	{
// 		for (int x = -6; x <= 6; x++)
// 		{
// 				// my_mlx_pixel_put(game->back, center_x + x, center_y + y,
// REDD);
// 			if (x * x + y * y <= 6 * 6)
// 			{
// 				my_mlx_pixel_put(game->back, minimap_x + x, minimap_y + y,
// REDD);
// 			}
// 		}
// 	}
// }

void	render_minimap(t_game *game)
{
	int x, y;
	int map_x, map_y;
	int center_x = 250;
	int center_y = 900;

	double cos_dir = cos(atan2(game->player.dir_y, game->player.dir_x));
	double sin_dir = sin(atan2(game->player.dir_y, game->player.dir_x));

	for (y = -MAP_RADIUS; y < MAP_RADIUS; y++)
	{
		for (x = -MAP_RADIUS; x < MAP_RADIUS; x++)
		{
			int distance = sqrt(x * x + y * y);
			if (distance < MAP_RADIUS)
			{
				int rotated_x = x * cos_dir - y * sin_dir;
				int rotated_y = x * sin_dir + y * cos_dir;
				int screen_x = center_x + rotated_x;
				int screen_y = center_y + rotated_y;
				map_x = (int)(game->player.pos_x + (rotated_x / MINI_CUBE));
				map_y = (int)(game->player.pos_y + (rotated_y / MINI_CUBE));
				if (map_x >= 0 && map_x < game->map->width && map_y >= 0
					&& map_y < game->map->height)
				{
					if (game->map->map[map_y][map_x] == '1')
					{
						my_mlx_pixel_put(game->back, screen_x, screen_y,
							0xFFFFFF);
					}
				}
			}
		}
	}
	// int x, y;
	// int map_x, map_y;
	// int center_x = 250;
	// int center_y = 900;
	// printf("pos_x = %f\n", game->player.pos_x);
	// printf("pos_y = %f\n", game->player.pos_y);
	// printf("dir_x = %f\n", game->player.dir_x);
	// printf("dir_y = %f\n", game->player.dir_y);

	// int map_center_x = game->player.pos_x * MINI_CUBE;
	// int map_center_y = game->player.pos_y * MINI_CUBE;

	// for (y = -MAP_RADIUS; y < MAP_RADIUS; y++)
	// {
	// 	for (x = -MAP_RADIUS; x < MAP_RADIUS; x++)
	// 	{

	// 		int distance = sqrt(x * x + y * y);
	// 		if (distance < MAP_RADIUS)
	// 		{
	// 			int screen_x = center_x + x;
	// 			int screen_y = center_y + y;
	// 			my_mlx_pixel_put(game->back, screen_x, screen_y, GREEN);
	// 			map_x = (map_center_x + x) / MINI_CUBE;
	// 			map_y = (map_center_y + y) / MINI_CUBE;
	// 			if (map_x >= 0 && map_x < game->map->width && map_y >= 0
	// 				&& map_y < game->map->height)
	// 			{
	// 				if (game->map->map[map_y][map_x] == '1')
	// 				{
	// 					my_mlx_pixel_put(game->back, screen_x, screen_y,
	// 						0xFFFFFF);
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// for (int y = -6; y <= 6; y++)
	// {
	// 	for (int x = -6; x <= 6; x++)
	// 	{
	// 			// my_mlx_pixel_put(game->back, center_x + x, center_y + y,
	// REDD);
	// 		if (x * x + y * y <= 6 * 6)
	// 		{
	// 			my_mlx_pixel_put(game->back, center_x + x, center_y + y, REDD);
	// 		}
	// 	}
	// }

	// int player_map_x = 100;
	// int player_map_y = 100;

	// // Render player as a small square
	// my_mlx_pixel_put(game->back, player_map_x, player_map_y, 0xFF0000);
	// my_mlx_pixel_put(game->back, player_map_x + 1, player_map_y, 0xFF0000);
	// my_mlx_pixel_put(game->back, player_map_x, player_map_y + 1, 0xFF0000);
	// my_mlx_pixel_put(game->back, player_map_x + 1, player_map_y + 1,
	// 0xFF0000);

	// // Render player's direction
	// int dir_x = player_map_x + cos(game->player.dir_x) * 5;
	// int dir_y = player_map_y + sin(game->player.dir_x) * 5;
	// my_mlx_pixel_put(game->back, dir_x, dir_y, 0xFF0000);
}