/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:56 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/12 13:02:50 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_sig_handler(int sig, siginfo_t *info, void *ptr)
{
	static char	byte;
	static int	count;
	int			res;

	(void)ptr;
	(void)info;
	if (sig == SIGUSR2)
		res = ft_append_bit_to_byte(1, &byte, &count);
	else
		res = ft_append_bit_to_byte(0, &byte, &count);
	if (res)
	{
		//ft_putchar_fd('(', 1);
		//ft_putnbr_fd(info->si_pid, 1);
		//ft_putchar_fd(')', 1);
		ft_putchar_fd(byte, 1);
	}
}

int	main(int argc, char const *argv[])
{
	struct sigaction	nsa;
	struct sigaction	osa[2];
	int					ret[2];

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
