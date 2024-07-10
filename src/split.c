/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:33:29 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/09 11:58:49 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static int	count_words(const char *str, char c)
// {
// 	int	i;
// 	int	trigger;

// 	i = 0;
// 	trigger = 0;
// 	while (*str)
// 	{
// 		if (*str != c && trigger == 0)
// 		{
// 			trigger = 1;
// 			i++;
// 		}
// 		else if (*str == c)
// 			trigger = 0;
// 		str++;
// 	}
// 	return (i);
// }

// static char	*word_dup(const char *str, int start, int finish)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	word = malloc((finish - start + 1) * sizeof(char));
// 	while (start < finish)
// 		word[i++] = str[start++];
// 	word[i] = '\0';
// 	return (word);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t i;
// 	size_t j;
// 	int index;
// 	char **split;

// 	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
// 	{
// 		return (0);
// 	}
// 	i = 0;
// 	j = 0;
// 	index = -1;
// 	while (i <= ft_strlen_gnl(s))
// 	{
// 		if (s[i] != c && index < 0)
// 		{
// 			index = i;
// 		}
// 		else if ((s[i] == c || i == ft_strlen_gnl(s)) && index >= 0)
// 		{
// 			split[j++] = word_dup(s, index, i);
// 			index = -1;
// 		}
// 		i++;
// 	}
// 	split[j] = NULL;
// 	return (split);
// }