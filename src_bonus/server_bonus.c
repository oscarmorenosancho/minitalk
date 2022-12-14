/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:56 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/14 13:25:20 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	ft_sig_handler(int sig, siginfo_t *info, void *ptr)
{
	t_sig_event	se;
	int			used;
	int			full;
	int			ret;

	(void)ptr;
	se.pid = info->si_pid;
	se.sig = sig;
	full = ft_is_full_se_queue(&used);
	if (used > QUEUE_SIZE / 8)
	{
		ft_putstr_fd("Notify queue in danger. Used:", 1);
		ft_putnbr_fd(used, 1);
		ft_putstr_fd("\n", 1);
		ret = kill(info->si_pid, SIGUSR2);
	}
	else
	{
		ret = kill(info->si_pid, SIGUSR1);
		if (! ft_push_se(se))
		{
			ft_log_error("Queue is full\n");
		}
	}
	if (ret == -1)
		ft_log_error("Kill failed\n");
}

int	main(int argc, char const *argv[])
{
	struct sigaction	nsa;
	sigset_t			set;
	struct sigaction	osa[3];
	int					ret[3];

	ft_init_se_queue();
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	nsa.sa_flags = SA_SIGINFO;
	nsa.sa_mask = set;
	nsa.sa_sigaction = ft_sig_handler;
	ft_check_server_args(argc, argv);
	ft_show_pid();
	ret[0] = sigaction(SIGUSR1, &nsa, &osa[0]);
	ret[1] = sigaction(SIGUSR2, &nsa, &osa[1]);
	ft_putstr_fd("Waiting for message from client...\n", 1);
	while (1)
	{
		ft_process_sig_ev();
		ft_process_sig_ev();
		pause();
	}
}
