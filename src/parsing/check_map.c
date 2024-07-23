/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:45:09 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/23 16:18:58 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_map_name(const char *av)
{
	char	*name_map;

	name_map = ft_strrchr(av, '.');
	if (name_map)
		return (!ft_strcmp(name_map, ".cub"));
	return (0);
}

t_dataList	*check_start_map(t_map *map, t_dataList *data)
{
	int	i;

	i = 0;
	while (data)
	{
		if (is_one_or_space(data->string))
		{
			map->start_map = i;
			return (data);
		}
		data = data->next;
		i++;
	}
	return (NULL);
}

t_dataList	*check_last_map(t_dataList *dataList)
{
	t_dataList	*last;

	last = ft_dbl_lstlast(dataList);
	while (!ft_strcmp(last->string, "\n"))
	{
		last = last->prev;
	}
	return (last);
}

t_dataList	*read_map(char *path)
{
	char		*line;
	int			fd;
	t_dataList	*data_list;

	data_list = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_exit("Could not open the file, check if the path is correct");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!data_list)
			data_list = ft_dbl_lstnew(line);
		else
			ft_dbl_lstadd_back(&data_list, ft_dbl_lstnew(line));
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
		error_exit("close");
	return (data_list);
}

void	check_all_init_params(t_map *map)
{
	if (!map->ea || !map->we || !map->so || !map->no || !map->floor
		|| !map->ceiling)
		error_exit("Not all parameters are initialized ");
}
