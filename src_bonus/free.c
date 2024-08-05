/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:12:12 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/06 00:28:21 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_string_array(map->map);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
	free_data_list(map->data);
	free(map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		free_all_textures(game);
		if (game->back)
		{
			free_image(game->mlx, game->back);
			game->back = NULL;
		}
		if (game->mlx_win)
		{
			mlx_destroy_window(game->mlx, game->mlx_win);
			game->mlx_win = NULL;
		}
		free(game->mlx);
	}
	free_map(game->map);
	free(game);
}

void	free_image(void *mlx, t_image *image)
{
	if (!image)
		return ;
	if (image->img)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
	}
	free(image);
}
