/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:12:12 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/23 16:18:58 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(t_map *map)
{
	free_string_array(map->map);
	free(map->no);
	free(map->ea);
	free(map->we);
	free(map->so);
	free(map->floor);
	free(map->ceiling);
	free(map);
}
