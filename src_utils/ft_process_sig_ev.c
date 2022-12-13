/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_sig_ev.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:33:51 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/13 11:54:01 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_utils.h"

static int	ft_update_exit_state(t_client_data	*client_data)
{
	if (client_data->exitcount == 2 && client_data->byte == '\\')
		return (1);
	if (client_data->exitcount < 2 && client_data->byte == '\\')
		client_data->exitcount++;
	else
		client_data->exitcount = 0;
	return (0);
}

void	ft_process_sig_ev(void)
{
	static t_list	*lst_clients;
	t_list			*client_node;
	t_client_data	*client_data;
	t_sig_event		se;
	int				res;

	ft_pop_se(&se);
	client_node = ft_lstfindfirst(lst_clients, &ft_node_is_pid, &se.pid);
	if (! client_node)
		client_node = ft_create_node_for_pid(&lst_clients, se.pid);
	client_data = client_node->content;
	if (se.sig == SIGUSR2)
		res = ft_append_bit_to_byte(1, &client_data->byte, &client_data->count);
	else
		res = ft_append_bit_to_byte(0, &client_data->byte, &client_data->count);
	if (res)
	{
		ft_putchar_fd(client_data->byte, 1);
		if (ft_update_exit_state(client_data))
		{
			ft_lstclear(&lst_clients, &free);
			exit (0);
		}
	}
}
