/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:44:42 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/23 16:18:58 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_parameter(t_map *map, char **parameters)
{
	if (!ft_strcmp(parameters[0], "NO") && !map->no)
		map->no = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "SO") && !map->so)
		map->so = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "WE") && !map->we)
		map->we = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "EA") && !map->ea)
		map->ea = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "F") && !map->floor)
		map->floor = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "C") && !map->ceiling)
		map->ceiling = ft_strdup(parameters[1]);
	else
		error_exit("Incorrect parameters in the file");
}

void	init_parameter(t_map *map, t_dataList *data)
{
	char	**parameters;
	int		i;
	int		size_params;

	i = 0;
	while (i < map->start_map)
	{
		if (ft_strcmp(data->string, "\n"))
		{
			data->string = remove_symb(data->string, '\n');
			parameters = ft_split(data->string, ' ');
			size_params = count_size_array(parameters);
			if (size_params != 2 && ft_strcmp(parameters[2], " "))
				error_exit("Invalid parameter format");
			check_parameter(map, parameters);
			free_string_array(parameters);
		}
		data = data->next;
		i++;
	}
}

unsigned int	init_colors(char *color_string)
{
	char			**rgb;
	unsigned int	colors[3];
	int				i;

	i = 0;
	rgb = ft_split(color_string, ',');
	if (count_size_array(rgb) != 3)
		error_exit("Wrong color format, there should be 3 numbers");
	while (rgb[i])
	{
		if (error_color(rgb[i]))
		{
			colors[i] = atoi(rgb[i]);
			if (colors[i] < 0 || colors[i] > 255)
				error_exit("The range must be from 0 to 255");
		}
		i++;
	}
	return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
}

void	init_map(t_map *map, t_dataList *data)
{
	t_dataList	*last;
	t_dataList	*head;
	int			i;

	last = check_last_map(data);
	head = check_start_map(map, data);
	init_parameter(map, data);
	check_all_init_params(map);
	map->color_floor = init_colors(map->floor);
	map->color_ceiling = init_colors(map->ceiling);
	i = 0;
	map->rows = ft_dbl_lstsize(head, last, &map->cols);
	map->map = (char **)malloc((map->rows + 1) * sizeof(char *));
	while (head != last->next)
	{
		map->map[i] = remove_symb(head->string, '\n');
		i++;
		head = head->next;
	}
	map->map[i] = NULL;
}

t_map	*check_init_map(char *path)
{
	t_dataList	*data;
	t_map		*map;

	data = read_map(path);
	if (!data)
	{
		error_exit("Error reading map");
	}
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	init_map(map, data);
	check_valid_map(map->map);
	return (map);
}
