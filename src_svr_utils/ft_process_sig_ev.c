/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_sig_ev.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:33:51 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 18:26:05 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_svr_utils.h"
#include "../src_utils/minitalk_utils.h"

static int	ft_update_exit_state(t_client_data	*client_data)
{
	int	len;

	if (client_data->byte == '\0' && client_data->msg)
	{
		len = ft_strlen_x(client_data->msg);
		if (len >= 2)
		{
			return (client_data->msg[len - 2] == '\\' && \
				client_data->msg[len - 1] == '\\');
		}
	}
	return (0);
}

static void	ft_show_msg(t_client_data *client_data)
{
	ft_putstr_fd("\nMessage sent by client pid: ", 1);
	ft_putnbr_fd(client_data->pid, 1);
	ft_putstr_fd("\n", 1);
	if (client_data->msg)
		ft_putstr_fd(client_data->msg, 1);
}

static void	ft_update_received(t_client_data *client_data)
{
	char	*buf;

	if (client_data && client_data->pid > 0)
	{
		if (client_data->byte)
		{
			ft_crc(&client_data->crc, client_data->byte);
			buf = ft_str_join_char(&client_data->msg, client_data->byte, \
				&client_data->len);
			client_data->msg = buf;
		}
	}
}

static void	ft_exit_server(t_list *lst_clients, t_client_data *client_data)
{
	ft_show_msg(client_data);
	ft_lstclear(&lst_clients, &ft_free_node);
	ft_putstr_fd("\nReceived close command\nServer exiting\n", 1);
	exit (0);
}

void	ft_process_sig_ev(int reset)
{
	static t_list	*lst_clients;
	t_list			*client_node;
	t_client_data	*client_data;
	t_sig_event		se;
	int				res;

	if (reset)
		ft_lstclear(&lst_clients, &ft_free_node);
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
		if (ft_update_exit_state(client_data))
			ft_exit_server(lst_clients, client_data);
		if (! client_data->byte)
			ft_show_msg(client_data);
		ft_clean_pid(&lst_clients, client_node, client_data->byte);
	}
}
