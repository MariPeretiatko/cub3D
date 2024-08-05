/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:45:25 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/06 00:43:25 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
