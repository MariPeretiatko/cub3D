/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:04:29 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/12 22:23:20 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

#define BUFFER_SIZE 100

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

size_t	ft_strlen_gnl(const char *str);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char const *s1, char const *s2);

char	*get_next_line(int fd);

#endif