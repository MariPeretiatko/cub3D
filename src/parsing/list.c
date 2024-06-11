#include "../../inc/cub3d.h"

//t_data_list	*ft_lstlast(t_data_list *lst)
//{
//    if (lst)
//    {
//        while (lst->next)
//        {
//            lst = lst->next;
//        }
//    }
//    return (lst);
//}
//
//void	ft_lstadd_back(t_data_list **lst, t_data_list  *new)
//{
//    if (!lst)
//        return ;
//    if (lst)
//    {
//        if (*lst)
//        {
//            ft_lstlast(*lst)->next = new;
//            return ;
//        }
//    }
//    *lst = new;
//}
//
//t_data_list 	*ft_lstnew(char *str)
//{
//    t_data_list 	*new_obj;
//
//    new_obj = (t_data_list  *)malloc(sizeof(t_data_list ));
//    if (new_obj)
//    {
//        new_obj->string = strdup(str);
//        new_obj->next = NULL;
//    }
//    return (new_obj);
//}
//
//int	ft_lstsize(t_data_list  *lst)
//{
//    int	i;
//
//    i = 0;
//    while (lst)
//    {
//        lst = lst->next;
//        i++;
//    }
//    return (i);
//}
//
//void free_data_list(t_data_list *list) {
//    t_data_list *temp;
//    while (list) {
//        temp = list;
//        list = list->next;
//        free(temp->string);
//        free(temp);
//    }
//}

t_data_list	*ft_lstlast(t_data_list *lst)
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

void	ft_lstadd_back(t_data_list **lst, t_data_list  *new_list)
{
    t_data_list	*tmp;

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

t_data_list 	*ft_lstnew(char *str)
{
    t_data_list 	*new_obj;

    new_obj = (t_data_list  *)malloc(sizeof(t_data_list ));
    if (new_obj)
    {
        new_obj->string = strdup(str);
        new_obj->prev = NULL;
        new_obj->next = NULL;
    }
    return (new_obj);
}

int	ft_lstsize(t_data_list  *start, t_data_list *end)
{
    int	i;

    i = 0;
    while (start != end->next)
    {
        start = start->next;
        i++;
    }
    return (i);
}

void free_data_list(t_data_list *head) {
    t_data_list	*current;
    t_data_list	*next;

    current = head;
    while (current != NULL)
    {
        next = current->next;
        free(current->string);
        free(current);
        current = next;
    }
}

//void ft_delete_node(t_data_list **list, t_data_list *node){
//    if (list == NULL || *list == NULL || node == NULL) {
//        return;
//    }
//
//    // Если узел является головным
//    if (*list == node) {
//        *list = node->next;
//    }
//
//    // Изменяем next, если узел не последний
//    if (node->next != NULL) {
//        node->next->prev = node->prev;
//    }
//
//    // Изменяем prev, если узел не первый
//    if (node->prev != NULL) {
//        node->prev->next = node->next;
//    }
//
//    // Освобождаем память, выделенную под данные и узел
//    free(node->string);
//    free(node);
//}

