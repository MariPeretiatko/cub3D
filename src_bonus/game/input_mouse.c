/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:49:59 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/05 19:15:34 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	mouse_move(int x, int y, t_game *game);
static int	mouse_hook(int button, int x, int y, t_game *param);
static void	scroll_up(t_game *game);
static void	scroll_down(t_game *game);

void	init_event_mouse(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->mlx_win);
	mlx_mouse_move(game->mlx, game->mlx_win, MIDWID, MIDHG);
	mlx_hook(game->mlx_win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->mlx_win, mouse_hook, game);
}

static int	mouse_hook(int keycode, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (keycode == KEY_MOUSE_LEFT)
		printf("%d KEY_MOUSE_LEFT\n", keycode);
	if (keycode == KEY_MOUSE_RIGHT)
		printf("%d KEY_MOUSE_RIGHT\n", keycode);
	if (keycode == MOUSE_SDOWN)
		scroll_down(game);
	if (keycode == MOUSE_SUP)
		scroll_up(game);
	return (0);
}

static void	scroll_up(t_game *game)
{
	if (game->type_weapon == BFG)
	{
		game->type_weapon = SHOTGUN;
		return ;
	}
	game->type_weapon++;
}

static void	scroll_down(t_game *game)
{
	if (game->type_weapon == SHOTGUN)
	{
		game->type_weapon = BFG;
		return ;
	}
	game->type_weapon--;
}

static int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x;

	if (x < SCREEN_WIDTH * 0.1 || x > SCREEN_WIDTH * 0.9 || y < SCREEN_HEIGHT
		* 0.1 || y > SCREEN_HEIGHT * 0.9)
	{
		mlx_mouse_move(game->mlx, game->mlx_win, MIDWID, MIDHG);
		last_x = MIDWID;
	}
	if (last_x < x)
		rotate_right(game);
	else
		rotate_left(game);
	last_x = x;
	return (0);
}
