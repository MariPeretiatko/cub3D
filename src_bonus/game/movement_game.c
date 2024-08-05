/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:25:41 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/05 19:03:00 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_front(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
		* game->player.dir_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
			* game->player.dir_y)] == 'O')
		game->player.pos_y = new_pos_y;
}

void	move_back(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.dir_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
		* game->player.dir_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
			* game->player.dir_y)] == 'O')
		game->player.pos_y = new_pos_y;
}

void	move_left(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x - DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
		* game->player.plane_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y - DISTANCE
			* game->player.plane_y)] == 'O')
		game->player.pos_y = new_pos_y;
}

void	move_right(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
	new_pos_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	if (game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == '0'
		|| game->map->map[(int)(new_pos_x + DISTANCE
			* game->player.plane_x)][(int)game->player.pos_y] == 'O')
		game->player.pos_x = new_pos_x;
	if (game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
		* game->player.plane_y)] == '0'
		|| game->map->map[(int)game->player.pos_x][(int)(new_pos_y + DISTANCE
			* game->player.plane_y)] == 'O')
		game->player.pos_y = new_pos_y;
}
