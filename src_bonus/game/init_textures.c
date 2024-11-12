/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:54:21 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/06 14:27:45 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_weapons_emblems(t_game *game);
static void	init_weapon_texture(t_game *game, t_image **texture,
				char *path_texture);

void	init_all_textures(t_game *game)
{
	init_walls(game);
	init_weapons_emblems(game);
}

void	init_walls(t_game *game)
{
	init_texture(game, &game->so_img, game->map->so, TEXWIDTH);
	init_texture(game, &game->no_img, game->map->no, TEXWIDTH);
	init_texture(game, &game->we_img, game->map->we, TEXWIDTH);
	init_texture(game, &game->ea_img, game->map->ea, TEXWIDTH);
	init_texture(game, &game->door, DOOR_PATH, TEXWIDTH);
}

static void	init_weapons_emblems(t_game *game)
{
	init_texture(game, &game->e_shotgun, SHOTGUN_E, EMBLEMSIZE);
	init_texture(game, &game->e_railgun, RAILGUN_E, EMBLEMSIZE);
	init_texture(game, &game->e_rocketl, ROCKETL_E, EMBLEMSIZE);
	init_texture(game, &game->e_bfg, BFG_E, EMBLEMSIZE);
	init_weapon_texture(game, &game->railgun, RAILGUN_PATH);
	init_weapon_texture(game, &game->shotgun, SHOTGUN_PATH);
	init_weapon_texture(game, &game->rocketl, ROCKETL_PATH);
	init_weapon_texture(game, &game->bfg, BFG_PATH);
}

void	init_texture(t_game *game, t_image **texture, char *path_texture,
		int size_texture)
{
	// int	size;
	// size = size_texture;
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

static void	init_weapon_texture(t_game *game, t_image **texture,
		char *path_texture)
{
	int	h;
	int	w;

	h = WEAPON_HEIGHT;
	w = WEAPON_WIDTH;
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
