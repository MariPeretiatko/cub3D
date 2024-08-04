/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:54:21 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/03 16:36:48 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_weapon_texture(t_game *game, t_image **texture,
				char *path_texture, int height, int width);

void	init_walls(t_game *game)
{
	init_texture(game, &game->so_img, game->map->so, TEXWIDTH);
	init_texture(game, &game->no_img, game->map->no, TEXWIDTH);
	init_texture(game, &game->we_img, game->map->we, TEXWIDTH);
	init_texture(game, &game->ea_img, game->map->ea, TEXWIDTH);
	
	init_texture(game, &game->door, "textures/door.xpm", TEXWIDTH);
	init_texture(game, &game->open_door, "textures/open_door.xpm", TEXWIDTH);
	init_texture(game, &game->e_shotgun, "textures/emblems/shotgun80.xpm",
		EMBLEMSIZE);
	init_texture(game, &game->e_railgun, "textures/emblems/railgun80.xpm",
		EMBLEMSIZE);
		init_texture(game, &game->e_rocketl, "textures/emblems/shotgun80.xpm",
		EMBLEMSIZE);
	init_texture(game, &game->e_bfg, "textures/emblems/bfg80.xpm",
		EMBLEMSIZE);
	init_weapon_texture(game, &game->railgun,
		"textures/weapons/railgun500_248.xpm", 248, 500);
	init_weapon_texture(game, &game->shotgun,
		"textures/weapons/shotgun500_248.xpm", 248, 500);
	init_weapon_texture(game, &game->rocketl,
		"textures/weapons/rocketl500_248.xpm", 248, 500);
		init_weapon_texture(game, &game->bfg,
		"textures/weapons/bfg500_248.xpm", 248, 500);
}

void	init_texture(t_game *game, t_image **texture, char *path_texture,
		int size_texture)
{
	int	size;

	size = size_texture;
	*texture = ft_calloc(1, sizeof(t_image));
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path_texture,
			&size_texture, &size_texture);
	if (!(*texture)->img)
		error_exit_game("Problem with loading image", game);
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	if (!(*texture)->addr)
		error_exit_game("Problem with getting image address", game);
}

void	init_weapon_texture(t_game *game, t_image **texture, char *path_texture,
		int height, int width)
{
	int h = height;
	int w = width;

	*texture = ft_calloc(1, sizeof(t_image));
	if (!(*texture))
		error_exit_game("Failed to allocate memory for weapon texture", game);
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path_texture, &w, &h);
	if (!(*texture)->img)
		error_exit_game("Problem with loading image", game);
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
	if (!(*texture)->addr)
		error_exit_game("Problem with getting image address", game);
}