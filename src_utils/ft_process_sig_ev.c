/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_sig_ev.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:33:51 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/14 12:23:38 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_utils.h"

static int	ft_update_exit_state(t_client_data	*client_data)
{
	if (client_data->exitcount == 2 && client_data->byte == '\0')
		return (1);
	if (client_data->exitcount < 2 && client_data->byte == '\\')
		client_data->exitcount++;
	else
		client_data->exitcount = 0;
	return (0);
}

/*static void	ft_print_received(t_client_data *client_data)
{
	if (client_data->byte)
		ft_putchar_fd(client_data->byte, 1);
	else
	{
		ft_putstr_fd("\nMessage over for client pid: ", 1);
		ft_putnbr_fd(client_data->pid, 1);
		ft_putstr_fd("\n", 1);
	}
}*/

static void	ft_update_received(t_client_data *client_data)
{
	char	*buf;

	if (client_data->byte)
	{
		buf = ft_str_join_char(&client_data->msg, client_data->byte);
		client_data->msg = buf;
	}
	else
	{
		ft_putstr_fd("\nMessage sent by client pid: ", 1);
		ft_putnbr_fd(client_data->pid, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(client_data->msg, 1);
	}
}

void	ft_process_sig_ev(void)
{
	static t_list	*lst_clients;
	t_list			*client_node;
	t_client_data	*client_data;
	t_sig_event		se;
	int				res;

	if (ft_is_empty_se_queue() || ! ft_pop_se(&se))
		return ;
	client_node = ft_lstfindfirst(lst_clients, &ft_content_is_pid, &se.pid);
	if (! client_node)
		client_node = ft_create_node_for_pid(&lst_clients, se.pid);
	client_data = client_node->content;
	res = ft_append_bit_to_byte(se.sig == SIGUSR2, \
		&client_data->byte, &client_data->count);
	if (res)
	{
		ft_update_received(client_data);
		ft_clean_pid(&lst_clients, client_node, client_data->byte);
		if (ft_update_exit_state(client_data))
		{
			ft_lstclear(&lst_clients, &ft_free_node);
			ft_putstr_fd("Received close command\nServer exiting\n", 1);
			exit (0);
		}
	}
}
