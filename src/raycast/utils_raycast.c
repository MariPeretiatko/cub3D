/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:00:57 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/22 16:12:17 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	*pixel;

	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0
		|| tex_x >= texture->width || tex_y >= texture->height)
		return (0);
	offset = tex_y * (texture->line_length / (texture->bits_per_pixel / 8))
		+ tex_x;
	pixel = (unsigned int *)(texture->addr + offset * (texture->bits_per_pixel
				/ 8));
	return (*pixel);
}

void	add_plane_characters(t_game *game)
{
	char	plane;

	plane = game->player.direction;
	if (plane == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
	}
	else if (plane == 'N')
	{
		game->player.dir_x = 1;
		game->player.plane_y = -0.66;
	}
	else if (plane == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = -0.66;
	}
	else if (plane == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = 0.66;
	}
}

int	check_directions(t_game *game)
{
	if (game->rc.side == 0)
	{
		if (game->rc.raydir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (game->rc.raydir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}
