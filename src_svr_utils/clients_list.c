/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:26:18 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/14 18:29:46 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_svr_utils.h"

int	ft_content_is_pid(unsigned int i, void *content, void *arg)
{
	t_client_data	*cd;
	pid_t			pid;

	(void)i;
	pid = *(pid_t *)arg;
	cd = (t_client_data *)content;
	return (cd->pid == pid);
}

int	ft_node_is_pid(unsigned int i, t_list *node, void *arg)
{
	t_client_data	*cd;
	pid_t			pid;

	(void)i;
	pid = *(pid_t *)arg;
	cd = (t_client_data *)node->content;
	return (cd->pid == pid);
}

t_list	*ft_create_node_for_pid(t_list	**lst_clients, pid_t pid)
{
	t_client_data	*cd;
	t_list			*node;

	cd = ft_calloc(1, sizeof(t_client_data));
	if (! cd)
		return (NULL);
	node = ft_lstnew(cd);
	if (! node)
	{
		free(cd);
		return (node);
	}
	cd->pid = pid;
	ft_lstadd_front(lst_clients, node);
	return (node);
}

void	ft_free_node(void *node)
{
	t_client_data	*nd;

	if (! node)
		return ;
	nd = node;
	free_x((void **)&nd->msg);
	free (node);
}

void	ft_clean_pid(t_list **lst, t_list *node, char byte)
{
	if (! byte)
		ft_lstdeletewhere(lst, &ft_node_is_pid, &ft_free_node, (void *)node);
}
