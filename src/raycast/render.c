/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:17 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/23 16:19:59 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	render(t_game *game)
{
	int	y;
	int	x;

	x = -1;
	render_floor_and_ceiling(game);
	while (++x < SCREEN_WIDTH)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			render_walls(game, x, y);
		}
	}
	moves_execute(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->back.img, 0, 0);
	return (0);
}

void	render_floor_and_ceiling(t_game *game)
{
	unsigned int	*dst;
	int				i;

	dst = (unsigned int *)game->back.addr;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_ceiling;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->color_floor;
}

void	render_walls(t_game *game, int x, int y)
{
	game->rc.tex_y = (int)game->rc.tex_pos & (game->walls[0].height - 1);
	game->rc.tex_pos += game->rc.step;
	game->rc.color = get_texture_pixel(&game->walls[check_directions(game)],
			game->rc.tex_x, game->rc.tex_y);
	my_mlx_pixel_put(&game->back, x, y, game->rc.color);
}
