/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:45:25 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/02 20:28:23 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// 040104
t_image	*active_get_type_emblem(t_game *game)
{
	if (game->type_weapon == SHOTGUN)
		return (game->e_shotgun);
	else if (game->type_weapon == RAILGUN)
		return (game->e_railgun);
	else if (game->type_weapon == ROCKETL)
		return (game->e_rocketl);
	else if (game->type_weapon == BFG)
		return (game->e_bfg);
	else
		return (game->e_shotgun);
}
t_image	*get_type_weapon(t_game *game)
{
	if (game->type_weapon == SHOTGUN)
		return (game->shotgun);
	else if (game->type_weapon == RAILGUN)
		return (game->railgun);
	else if (game->type_weapon == ROCKETL)
		return (game->rocketl);
	else if (game->type_weapon == BFG)
		return (game->bfg);
	else
		return (game->current_weapon);
}

void	render_weapon(t_game *game)
{
	unsigned int	color;
	int				draw_x_start;
	int				draw_y_start;

	int x, y;
	game->current_weapon = get_type_weapon(game);
	x = 0;
	draw_x_start = SCREEN_WIDTH * 0.90 - 500;
	draw_y_start = SCREEN_HEIGHT - 248;
	while (x < 500)
	{
		y = 0;
		while (y < 248)
		{
			color = get_texture_pixel(game->current_weapon, x, y);
			if (color != BLACK)
			{
				my_mlx_pixel_put(game->back, draw_x_start + x, draw_y_start + y,
					color);
			}
			y++;
		}
		x++;
	}
}

void	show_panel(t_game *game)
{
	int				x_pos;
	int				y_pos;
	int				x;
	int				y;
	unsigned int	color;
	int				draw_x;
	int				draw_y;
	t_image			*emblem;

	emblem = active_get_type_emblem(game);
	x_pos = SCREEN_HEIGHT * 0.2;
	y_pos = SCREEN_WIDTH * 0.2;
	x = 0;
	y = 0;
	while (x++ < SCREEN_HEIGHT && x < 80)
	{
		y = 0;
		while (y++ < SCREEN_WIDTH && y < 80)
		{
			color = get_texture_pixel(emblem, x, y);
			if (color != BLACK)
			{
				draw_x = x_pos + x;
				draw_y = y_pos + y;
				if (draw_x >= 0 && draw_x < SCREEN_WIDTH && draw_y >= 0
					&& draw_y < SCREEN_HEIGHT)
				{
					my_mlx_pixel_put(game->back, draw_x, draw_y, color);
				}
			}
		}
	}
}

void	render_gun(t_game *game)
{
	(void)game;
	// int				x_pos;
	// int				y_pos;
	// int				x;
	// int				y;
	// unsigned int	color;
	// int				draw_x;
	// int				draw_y;
	// x_pos = 500;
	// y_pos = 500;
	// x = 0;
	// y = 0;
	// while (x++ < SCREEN_HEIGHT && x < 80)
	// {
	// 	y = 0;
	// 	while (y++ < SCREEN_WIDTH && y < 80)
	// 	{
	// 		color = get_texture_pixel(game->e_shotgun, x, y);
	// 		// if (x_pos + x >= 0 && x_pos + x < SCREEN_WIDTH && y
	// 		// + y_pos >= 0&& y_pos + y < SCREEN_HEIGHT) {
	// 		//         my_mlx_pixel_put(game->back, x_pos + x, y_pos + y,color);
	// 		//     }
	// 		// my_mlx_pixel_put(game->back, x_pos + x, y_pos + y, color);
	// 		if (color != BLACK)
	// 		{ // Assuming BLACK is 0x000000
	// 			draw_x = x_pos + x;
	// 			draw_y = y_pos + y;
	// 			// Check boundaries before drawing the pixel
	// 			if (draw_x >= 0 && draw_x < SCREEN_WIDTH && draw_y >= 0
	// 				&& draw_y < SCREEN_HEIGHT)
	// 			{
	// 				my_mlx_pixel_put(game->back, draw_x, draw_y, color);
	// 			}
	// 		}
	// 	}
	// }
	// x_pos = 500;
	// y_pos = 600;
	// x = 0;
	// y = 0;
	// while (x++ < SCREEN_HEIGHT && x < 80)
	// {
	// 	y = 0;
	// 	while (y++ < SCREEN_WIDTH && y < 80)
	// 	{
	// 		color = get_texture_pixel(game->e_railgun, x, y);
	// 		// if (x_pos + x >= 0 && x_pos + x < SCREEN_WIDTH && y
	// 		// + y_pos >= 0&& y_pos + y < SCREEN_HEIGHT) {
	// 		//         my_mlx_pixel_put(game->back, x_pos + x, y_pos + y,color);
	// 		//     }
	// 		// my_mlx_pixel_put(game->back, x_pos + x, y_pos + y, color);
	// 		if (color != 0x000000)
	// 		{ // Assuming BLACK is 0x000000
	// 			draw_x = x_pos + x;
	// 			draw_y = y_pos + y;
	// 			// Check boundaries before drawing the pixel
	// 			if (draw_x >= 0 && draw_x < SCREEN_WIDTH && draw_y >= 0
	// 				&& draw_y < SCREEN_HEIGHT)
	// 			{
	// 				my_mlx_pixel_put(game->back, draw_x, draw_y, color);
	// 			}
	// 		}
	// 	}
	// }
}
