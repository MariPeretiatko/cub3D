/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:11:55 by mperetia          #+#    #+#             */
/*   Updated: 2024/06/15 00:00:06 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_dataList	*ft_lstlast(t_dataList *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void	ft_lstadd_back(t_dataList **lst, t_dataList *new_list)
{
	t_dataList	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new_list;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	new_list->prev = tmp;
	tmp->next = new_list;
}

t_dataList	*ft_lstnew(char *str)
{
	t_dataList	*new_obj;

	new_obj = (t_dataList *)malloc(sizeof(t_dataList));
	if (new_obj)
	{
		new_obj->string = strdup(str);
		new_obj->prev = NULL;
		new_obj->next = NULL;
	}
	return (new_obj);
}

int	ft_lstsize(t_dataList *start, t_dataList *end, int *cols)
{
	int	i;
	int	tmp;

	i = 0;
	while (start != end->next)
	{
		tmp = strlen(start->string) - 1;
		if (*cols < tmp)
			*cols = tmp;
		start = start->next;
		i++;
	}
	return (i);
}

void	free_data_list(t_dataList *head)
{
	t_dataList	*current;
	t_dataList	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->string);
		free(current);
		current = next;
	}
}
