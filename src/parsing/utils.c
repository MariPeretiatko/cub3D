/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:14:01 by mperetia          #+#    #+#             */
/*   Updated: 2024/06/14 23:14:01 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_string_array(char **array)
{
	if (!array)
	{
		return ;
	}
	for (int i = 0; array[i]; i++)
	{
		free(array[i]);
	}
	free(array);
}

char	*remove_symb(char *input_string, char symb)
{
	size_t	length;
	char	*new_string;
	size_t	j;

	length = strlen(input_string);
	new_string = (char *)malloc(length + 1);
	if (!new_string)
		return (NULL);
	j = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (input_string[i] != symb)
		{
			new_string[j++] = input_string[i];
		}
	}
	new_string[j] = '\0';
	return (new_string);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	int len;
	int i;
	int j;

	len = (int)ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}