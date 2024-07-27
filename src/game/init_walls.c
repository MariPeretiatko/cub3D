/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:54:21 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/27 22:46:58 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_walls(t_game *game)
{
	init_texture(game, &game->so_img, game->map->so);
	init_texture(game, &game->no_img, game->map->no);
	init_texture(game, &game->we_img, game->map->we);
	init_texture(game, &game->ea_img, game->map->ea);
	init_texture(game, &game->gun,
		"/home/mperetia/sgoinfre/lasr_github/textures/railgun123.xpm");
}

void	init_texture(t_game *game, t_image **texture, char *path_texture)
{
	int	size;

	size = TEXWIDTH;
	*texture = ft_calloc(1, sizeof(t_image));
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path_texture, &size,
			&size);
	if (!(*texture)->img)
		error_exit_game("Problem with loading image", game);
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	if (!(*texture)->addr)
		error_exit_game("Problem with getting image address", game);
}
