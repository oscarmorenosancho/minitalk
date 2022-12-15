/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:56 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 17:05:42 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "../src_svr_utils/minitalk_svr_utils.h"

static int	ft_send_not_accepted(pid_t pid)
{
	static int	count;

	count++;
	ft_log_error("Not accepted, server too busy\n");
	if (count > 10)
	{
		ft_log_error("Too repetitions of server to busy\n");
		ft_putstr_fd("Discard data and reset queue\n", 2);
		ft_init_se_queue();
	}
	return (kill(pid, SIGUSR2));
}

static void	ft_process_n_events(int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		ft_process_sig_ev(0);
}

static void	ft_sig_handler(int sig, siginfo_t *info, void *ptr)
{
	t_sig_event	se;
	int			ret;

	(void)ptr;
	se.pid = info->si_pid;
	se.sig = sig;
	if (! ft_push_se(se))
		ret = ft_send_not_accepted(info->si_pid);
	else
		ret = kill(info->si_pid, SIGUSR1);
	if (ret == -1)
		ft_log_error("Kill failed\n");
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
		ft_process_n_events(2);
		pause();
	}
}
