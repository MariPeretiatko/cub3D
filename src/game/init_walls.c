/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:54:21 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/25 23:14:15 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_texture(t_game *game, char *path_texture, t_image *texture)
{
	int	size;

	size = 512;
	texture->img = mlx_xpm_file_to_image(game->mlx, path_texture, &size, &size);
	if (!texture->img)
		error_exit_game("Problem with loading image", game);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		error_exit_game("Problem with getting image address", game);
}

void	init_walls(t_game *game)
{
	game->no_img = malloc(sizeof(t_image));
	game->so_img = malloc(sizeof(t_image));
	game->we_img = malloc(sizeof(t_image));
	game->ea_img = malloc(sizeof(t_image));
	if (!game->no_img || !game->so_img || !game->we_img || !game->ea_img)
		error_exit_game("Failed to allocate memory for image", game);
	init_texture(game, game->map->so, game->so_img);
	init_texture(game, game->map->no, game->no_img);
	init_texture(game, game->map->we, game->we_img);
	init_texture(game, game->map->ea, game->ea_img);
}
