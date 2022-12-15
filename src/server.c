/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:56 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 17:03:25 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "../src_svr_utils/minitalk_svr_utils.h"

static void	ft_sig_handler(int sig, siginfo_t *info, void *ptr)
{
	t_sig_event	se;

	(void)ptr;
	se.pid = info->si_pid;
	se.sig = sig;
	if (! ft_push_se(se))
		ft_log_error("Queue is full\n");
}

static void	ft_check_sigaction_ret(int *ret)
{
	if (ret[0] == -1 || ret[1] == -1)
	{
		ft_log_error("sigaction failed\n");
		exit (-1);
	}
}

int	main(int argc, char const *argv[])
{
	struct sigaction	nsa;
	sigset_t			set;
	struct sigaction	osa[3];
	int					ret[3];

	ft_init_se_queue();
	sigemptyset(&set);
	nsa.sa_flags = SA_SIGINFO;
	nsa.sa_mask = set;
	nsa.sa_sigaction = ft_sig_handler;
	ft_check_server_args(argc, argv);
	ft_show_pid();
	ret[0] = sigaction(SIGUSR1, &nsa, &osa[0]);
	ret[1] = sigaction(SIGUSR2, &nsa, &osa[1]);
	ft_check_sigaction_ret(ret);
	ft_putstr_fd("Waiting for message from client...\n", 1);
	while (1)
	{
		ft_process_sig_ev(0);
		ft_process_sig_ev(0);
		pause();
	}
}
