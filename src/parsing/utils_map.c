/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:13:46 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/10 18:07:57 by mperetia         ###   ########.fr       */
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

void	check_parameter(t_map *map, char **parameters)
{
	if (!ft_strcmp(parameters[0], "NO") && !map->NO)
		map->NO = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "SO") && !map->SO)
		map->SO = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "WE") && !map->WE)
		map->WE = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "EA") && !map->EA)
		map->EA = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "F") && !map->floor)
		map->floor = ft_strdup(parameters[1]);
	else if (!ft_strcmp(parameters[0], "C") && !map->ceiling)
		map->ceiling = ft_strdup(parameters[1]);
	else
		error_exit("Incorrect parameters in the file");
}

int	count_size_array(char **array)
{
	int	count;

	count = 0;
	while (array[count])
		count++;
	return (count);
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

bool	is_one_or_space(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (false);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\f' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\t' && str[i] != '\v')
		{
			return (false);
		}
		i++;
	}
	return (true);
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
	if (!map->EA || !map->WE || !map->SO || !map->NO || !map->floor
		|| !map->ceiling)
		error_exit("Not all parameters are initialized ");
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

bool	error_color(char *rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (!ft_isdigit(rgb[i]))
			error_exit("The color parameter should contain only numbers");
		if (i >= 4)
			error_exit("Numbers in color should be no more than 3");
		i++;
	}
	return (true);
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
