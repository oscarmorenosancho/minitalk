/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:56 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/12 17:14:44 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_node_is_pid(unsigned int i, void *content, void *arg)
{
	t_client_data	*cd;
	pid_t			pid;

	(void)i;
	pid = *(pid_t *)arg;
	cd = (t_client_data *)content;
	return (cd->pid == pid);
}

static t_list	*ft_create_node_for_pid(t_list	**lst_clients, pid_t pid)
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

static void	ft_sig_handler(int sig, siginfo_t *info, void *ptr)
{
	static t_list	*lst_clients;
	t_list			*client_node;
	t_client_data	*client_data;
	int				res;

	(void)ptr;
	client_node = ft_lstfindfirst(lst_clients, &ft_node_is_pid, &info->si_pid);
	if (! client_node)
		client_node = ft_create_node_for_pid(&lst_clients, info->si_pid);
	client_data = client_node->content;
	if (sig == SIGUSR2)
		res = ft_append_bit_to_byte(1, &client_data->byte, &client_data->count);
	else
		res = ft_append_bit_to_byte(0, &client_data->byte, &client_data->count);
	if (res)
	{
		ft_putchar_fd(client_data->byte, 1);
		if (client_data->exitcount == 2 && client_data->byte == '\\')
		{
			ft_lstclear(&lst_clients, &free);
			exit (0);
		}
		if (client_data->exitcount < 2 && client_data->byte == '\\')
			client_data->exitcount++;
		else
			client_data->exitcount = 0;
	}
}

int	main(int argc, char const *argv[])
{
	struct sigaction	nsa;
	struct sigaction	osa[3];
	int					ret[3];

	nsa.sa_flags = SA_SIGINFO;
	nsa.sa_sigaction = ft_sig_handler;
	ft_check_server_args(argc, argv);
	ft_show_pid();
	ret[0] = sigaction(SIGUSR1, &nsa, &osa[0]);
	ret[1] = sigaction(SIGUSR2, &nsa, &osa[1]);
	ft_putstr_fd("Waiting for message from client...\n", 1);
	while (1)
		pause();
}
