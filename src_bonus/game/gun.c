/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:45:25 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/05 23:09:24 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	int				x;
	int				y;

	game->current_weapon = get_type_weapon(game);
	x = 0;
	draw_x_start = SCREEN_WIDTH * 0.90 - WEAPON_WIDTH;
	draw_y_start = SCREEN_HEIGHT - WEAPON_HEIGHT;
	while (x < WEAPON_WIDTH)
	{
		y = 0;
		while (y < WEAPON_HEIGHT)
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

void	draw_pixel(t_game *game, int pos_x, int pos_y, int x, int y, int color)
{
	int	draw_x;
	int	draw_y;

	draw_x = pos_x + x;
	draw_y = pos_y + y;
	if (draw_x >= 0 && draw_x < SCREEN_WIDTH && draw_y >= 0
		&& draw_y < SCREEN_HEIGHT)
		my_mlx_pixel_put(game->back, draw_x, draw_y, color);
}

void	render_emblem(t_game *game, t_image *emblem, int pos_x, int pos_y)
{
	int		x;
	int		y;
	int		color;
	bool	active;

	x = 0;
	if (active_get_type_emblem(game) == emblem)
		active = true;
	else
		active = false;
	while (x < SCREEN_HEIGHT && x < EMBLEMSIZE)
	{
		y = 0;
		while (y < SCREEN_WIDTH && y < EMBLEMSIZE)
		{
			color = get_texture_pixel(emblem, x, y);
			if ((!active && color != YELLOW && color != BLACK
					&& color != BLACK_) || (active && color != BLACK
					&& color != BLACK_))
				draw_pixel(game, pos_x, pos_y, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_emblems(t_game *game)
{
	render_emblem(game, game->e_shotgun, SCREEN_WIDTH
		* 0.4, SCREEN_HEIGHT * 0.65);
	render_emblem(game, game->e_rocketl, SCREEN_WIDTH * 0.4 + EMBLEMSIZE, SCREEN_HEIGHT * 0.65);
	// render_emblem(game, game->e_railgun, SCREEN_HEIGHT * 0.2, SCREEN_WIDTH
	// 	* 0.2 + (EMBLEMSIZE * RAILGUN) + 10);
	// render_emblem(game, game->e_bfg, SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.7);
	// rende_emblem(game, game->e_bfg, SCREEN_HEIGHT * 0.2, SCREEN_WIDTH
	// 	* 0.2 + (EMBLEMSIZE * BFG) + 10);
}

void	show_panel(t_game *game)
{
	render_emblems(game);
	// int				x_pos;
	// int				y_pos;
	// int				x;
	// int				y;
	// unsigned int	color;
	// int				draw_x;
	// int				draw_y;
	// t_image			*emblem;
	// emblem = active_get_type_emblem(game);
	// x_pos = SCREEN_HEIGHT * 0.2;
	// y_pos = SCREEN_WIDTH * 0.2;
	// x = 0;
	// y = 0;
	// while (x++ < SCREEN_HEIGHT && x < EMBLEMSIZE)
	// {
	// 	y = 0;
	// 	while (y++ < SCREEN_WIDTH && y < EMBLEMSIZE)
	// 	{
	// 		color = get_texture_pixel(emblem, x, y);
	// 		if (color != YELLOW && color != BLACK && color != BLACK_)
	// 		{
	// 			draw_x = x_pos + x;
	// 			draw_y = y_pos + y;
	// 			if (draw_x >= 0 && draw_x < SCREEN_WIDTH && draw_y >= 0
	// 				&& draw_y < SCREEN_HEIGHT)
	// 			{
	// 				my_mlx_pixel_put(game->back, draw_x, draw_y, color);
	// 			}
	// 		}
	// 	}
	// }
}
