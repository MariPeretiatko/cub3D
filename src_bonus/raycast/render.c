/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:17 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/06 13:32:58 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	render_floor_and_ceiling(t_game *game);
static void	render_walls(t_game *game, int x, int y);
static void	draw_crosshair(t_game *game);
// static void	render_door(t_game *game, int x, int y);

int	render(t_game *game)
{
	int	y;
	int	x;

	x = -1;
	render_floor_and_ceiling(game);
	update_status_door(game);
	while (++x < SCREEN_WIDTH)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
			render_walls(game, x, y);
	}
	render_weapon(game);
	draw_minimap(game, game->map, &game->player);
	draw_crosshair(game);
	moves_execute(game);
	show_panel(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->back->img, 0, 0);
	return (0);
}

static void	render_floor_and_ceiling(t_game *game)
{
	unsigned int	*dst;
	int				i;

	dst = (unsigned int *)game->back->addr;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_ceiling;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_floor;
}

static void	render_walls(t_game *game, int x, int y)
{
	if (game->map->map[game->rc.map_x][game->rc.map_y] == 'D')
	{
		render_door(game, x, y);
	}
	else
	{
		game->rc.tex_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
		game->rc.tex_pos += game->rc.step;
		game->rc.color = get_texture_pixel(get_texture_directions(game),
				game->rc.tex_x, game->rc.tex_y);
		my_mlx_pixel_put(game->back, x, y, game->rc.color);
	}
}

static void	draw_crosshair(t_game *game)
{
	int	center_x;
	int	center_y;
	int	x;
	int	y;
	int	crosshair_size;

	center_x = SCREEN_WIDTH / 2;
	center_y = SCREEN_HEIGHT / 2;
	crosshair_size = 12;
	x = center_x - crosshair_size;
	while (x <= center_x + crosshair_size)
	{
		my_mlx_pixel_put(game->back, x, center_y, GREEN);
		x++;
	}
	y = center_y - crosshair_size;
	while (y <= center_y + crosshair_size)
	{
		my_mlx_pixel_put(game->back, center_x, y, GREEN);
		y++;
	}
}
