/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:38:48 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/06 14:48:05 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void		render_emblems(t_game *game);
static void		render_emblem(t_game *game, t_image *emblem, int pos_x,
					int pos_y);
static t_image	*active_get_type_emblem(t_game *game);
// static void	draw_pixel(t_game *game, int pos_x, int pos_y, int x, int y,
		int color);
int	show_panel(t_game *game)
{
	struct timeval				tv;
	static unsigned long long	last_time;

	gettimeofday(&tv, NULL);
	game->diff += (tv.tv_sec * 1000 + (tv.tv_usec / 1000)) - last_time;
	last_time = (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
	if (game->diff < 1500 && game->show_panel)
	{
		render_emblems(game);
		return (0);
	}
	game->show_panel = false;
	game->diff = 0;
	return (0);
}

static void	render_emblems(t_game *game)
{
	render_emblem(game, game->e_shotgun, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT
		* 0.65);
	render_emblem(game, game->e_rocketl, SCREEN_WIDTH * 0.4 + EMBLEMSIZE,
		SCREEN_HEIGHT * 0.65);
	render_emblem(game, game->e_railgun, SCREEN_WIDTH * 0.4 + EMBLEMSIZE * 2,
		SCREEN_HEIGHT * 0.65);
	render_emblem(game, game->e_bfg, SCREEN_WIDTH * 0.4 + EMBLEMSIZE * 3,
		SCREEN_HEIGHT * 0.65);
}

static void	render_emblem(t_game *game, t_image *emblem, int pos_x, int pos_y)
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
				my_mlx_pixel_put(game->back, pos_x + x, pos_y + y, color);
			y++;
		}
		x++;
	}
}

static t_image	*active_get_type_emblem(t_game *game)
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
