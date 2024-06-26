/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:12:12 by mperetia          #+#    #+#             */
/*   Updated: 2024/06/14 23:53:04 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(t_map *map)
{
	free_string_array(map->map);
	free(map->NO);
	free(map->EA);
	free(map->WE);
	free(map->SO);
	free(map->floor);
	free(map->ceiling);
	free(map);
}
