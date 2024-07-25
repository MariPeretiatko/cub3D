/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:14:01 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/25 23:13:45 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// free?
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

char	*remove_symb(char *input_string, char symb)
{
	size_t	length;
	char	*new_string;
	size_t	j;
	size_t	i;

	length = ft_strlen(input_string);
	new_string = (char *)malloc(length + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	j = 0;
	while (i < length)
	{
		if (input_string[i] != symb)
			new_string[j++] = input_string[i];
		i++;
	}
	new_string[j] = '\0';
	return (new_string);
}

int	count_size_array(char **array)
{
	int	count;

	count = 0;
	while (array[count])
		count++;
	return (count);
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

bool	error_color(char **rgb, t_map *map, int j)
{
	int	i;

	i = 0;
	while (rgb[j][i])
	{
		if (!ft_isdigit(rgb[j][i]))
			error_exit_map_array("Color params only numbers", map, rgb);
		if (i >= 3)
			error_exit_map_array("Numbers color no more 3", map, rgb);
		i++;
	}
	return (true);
}
