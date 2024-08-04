/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:00:57 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/29 13:27:16 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

int	get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	*pixel;

	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0
		|| tex_x >= TEXWIDTH || tex_y >= TEXHEIGHT)
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
		game->player.dir_x = 1;
		game->player.plane_y = -0.66;
	}
	else if (plane == 'N')
	{
		game->player.dir_x = -1;
		game->player.plane_y = 0.66;
	}
	else if (plane == 'E')
	{
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
	}
	else if (plane == 'W')
	{
		game->player.dir_y = -1;
		game->player.plane_x = -0.66;
	}
}

t_image	*get_texture_directions(t_game *game)
{
	if (game->rc.side == 0)
	{
		if (game->rc.raydir_x > 0)
			return (game->so_img);
		else
			return (game->no_img);
	}
	else
	{
		if (game->rc.raydir_y > 0)
			return (game->ea_img);
		else
			return (game->we_img);
	}
}
