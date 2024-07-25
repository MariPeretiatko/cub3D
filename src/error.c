/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:12:05 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/25 23:04:41 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_exit(char *mes)
{
	printf("%s\n", mes);
	exit(0);
}

void	error_exit_game(char *mes, t_game *game)
{
	free_game(game);
	printf("%s\n", mes);
	exit(0);
}

void	print_data(t_dataList *data)
{
	while (data)
	{
		printf("%s", data->string);
		data = data->next;
	}
}

void	error_exit_map(char *mes, t_map *map)
{
	free_map(map);
	printf("%s\n", mes);
	exit(0);
}

void	error_exit_data_list(char *mes, t_dataList *data)
{
	free_data_list(data);
	printf("%s\n", mes);
	exit(0);
}

void	error_exit_map_array(char *mes, t_map *map, char **array)
{
	free_string_array(array);
	free_map(map);
	printf("%s\n", mes);
	exit(0);
}
