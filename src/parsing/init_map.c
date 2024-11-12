/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:44:42 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/28 12:10:50 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void			init_map(t_map *map, t_dataList *data);
static void			init_parameter(t_map *map, t_dataList *data);
static void			check_parameter(t_map *map, char **params);
static unsigned int	init_colors(char *color_string, t_map *map);

t_map	*check_init_map(char *path)
{
	t_dataList	*data;
	t_map		*map;

	data = read_map(path);
	if (!data)
		error_exit("Error reading map");
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		error_exit_data_list("Failed to allocate memory for map", data);
	map->data = data;
	init_map(map, map->data);
	check_valid_map(map);
	return (map);
}

static void	init_map(t_map *map, t_dataList *data)
{
	t_dataList	*last;
	t_dataList	*head;
	int			i;

	last = check_last_map(data);
	head = check_start_map(map, data);
	init_parameter(map, data);
	if (!check_all_init_params(map))
		error_exit_map("Not all parameters are initialized", map);
	map->color_floor = init_colors(map->floor, map);
	map->color_ceiling = init_colors(map->ceiling, map);
	i = 0;
	map->height = ft_dbl_lstsize(head, last, &map->width);
	map->map = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!map->map)
		error_exit_map("Failed to allocate memory for map", map);
	while (head != last->next)
	{
		map->map[i] = remove_symb(head->string, '\n');
		i++;
		head = head->next;
	}
	map->map[i] = NULL;
}

static void	init_parameter(t_map *map, t_dataList *data)
{
	char	**params;
	int		i;
	int		size_params;
	char	*tmp;

	i = 0;
	while (i < map->start_map)
	{
		if (ft_strcmp(data->string, "\n"))
		{
			tmp = remove_symb(data->string, '\n');
			free(data->string);
			data->string = tmp;
			params = ft_split(data->string, ' ');
			size_params = count_size_array(params);
			if (size_params != 2)
				error_exit_map_array("Invalid parameter format", map, params);
			check_parameter(map, params);
			free_string_array(params);
		}
		data = data->next;
		i++;
	}
}

static void	check_parameter(t_map *map, char **params)
{
	if (!ft_strcmp(params[0], "NO") && !map->no)
		map->no = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "SO") && !map->so)
		map->so = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "WE") && !map->we)
		map->we = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "EA") && !map->ea)
		map->ea = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "F") && !map->floor)
		map->floor = ft_strdup(params[1]);
	else if (!ft_strcmp(params[0], "C") && !map->ceiling)
		map->ceiling = ft_strdup(params[1]);
	else
		error_exit_map_array("Incorrect parameters in the file", map, params);
}

static unsigned int	init_colors(char *color_string, t_map *map)
{
	char			**rgb;
	unsigned int	colors[3];
	int				i;

	i = 0;
	if (color_string != NULL)
	{
		rgb = ft_split(color_string, ',');
		if (count_size_array(rgb) != 3)
			error_exit_map_array("Wrong color format 3 numbers", map, rgb);
		while (rgb[i])
		{
			if (error_color(rgb, map, i))
			{
				colors[i] = ft_atoi(rgb[i]);
				// if (colors[i] < 0 || colors[i] > 255)
				if (colors[i] > 255)
					error_exit_map_array("The range must 0 to 255", map, rgb);
			}
			i++;
		}
		free_string_array(rgb);
		return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
	}
	return (0);
}
