/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:49:59 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/27 18:59:58 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	mouse_hook(int keycode, t_game *game);
static int	mouse_move(int x, int y, t_game *game);

void	init_event_mouse(t_game *game)
{
	// middle of screen
	mlx_mouse_hide(game->mlx, game->mlx_win);
	mlx_mouse_move(game->mlx, game->mlx_win, MIDWID, MIDHG);
	// mlx_do_sync(game->mlx);
	mlx_hook(game->mlx_win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->mlx_win, mouse_hook, &game);
}

static int	mouse_hook(int keycode, t_game *game)
{
	if (keycode == KEY_MOUSE_LEFT)
		printf("%d KEY_MOUSE_LEFT\n", keycode);
	if (keycode == KEY_MOUSE_RIGHT)
		printf("%d KEY_MOUSE_RIGHT\n", keycode);
	if (keycode == MOUSE_SDOWN)
		printf("%d MOUSE_SDOWN\n", keycode);
	if (keycode == MOUSE_SUP)
		printf("%d MOUSE_SUP\n", keycode);
	(void)game;
	return (0);
}

static int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x;

	(void)y;
	if (x < 0 || x > SCREEN_WIDTH - 100 || y < 0 || y > SCREEN_HEIGHT - 100)
	{
		// printf("before x = %d\ny = %d\n\n", x, y);
		mlx_mouse_move(game->mlx, game->mlx_win, MIDWID, MIDHG);
		last_x = MIDWID;
		// printf("after x = %d\ny = %d\n\n", MIDWID,  MIDHG);
	}
	if (last_x < x)
	{
		rotate_right(game);
	}
	else
	{
		rotate_left(game);
	}
	last_x = x;
	return (0);
}
