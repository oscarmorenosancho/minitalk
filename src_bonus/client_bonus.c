/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:46:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 15:12:06 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "../src_cli_utils/minitalk_cli_utils.h"

#define INTERVAL_US	50

static void	ft_show_refused_n_exit(void)
{
	ft_log_error("Server refused the communication because its too busy\n");
	exit (-1);
}

static int	ft_send_bit_to_pid(int pid, int bit, useconds_t u)
{
	int	ret;
	int	pending;
	int	i;

	pending = ft_get_feedback_pending();
	ft_set_feedback_pending(pending + 1);
	if (bit)
		ret = kill(pid, SIGUSR2);
	else
		ret = kill(pid, SIGUSR1);
	if (ret == -1)
		ft_show_kill_error_n_exit();
	i = 0;
	while (ft_get_feedback_pending() > 0)
	{
		if (i > 3)
		{
			ft_log_error("Timeout waiting for ACK\n");
			exit (1);
		}
		i++;
		usleep(u * i);
	}
	usleep(u);
	return (ft_get_queue_hi());
}

static void	ft_send_byte_to_pid(int pid, char byte, useconds_t u)
{
	int	counter;
	int	bit;

	counter = 0;
	while (! ft_take_bit_from_byte(byte, &bit, &counter))
	{
		if (ft_send_bit_to_pid(pid, bit, u))
			ft_show_refused_n_exit();
	}
	if (ft_send_bit_to_pid(pid, bit, u))
		ft_show_refused_n_exit();
}

static void	ft_sig_handler(int sig)
{
	(void)sig;
	ft_dec_feedback_pending();
	if (sig == SIGUSR2)
		ft_putstr_fd("Received server too busy\n", 1);
	ft_set_queue_hi(sig == SIGUSR2);
	return ;
}

int	main(int argc, char const *argv[])
{
	t_client_args	args;
	int				i;

	ft_set_feedback_pending(0);
	ft_get_client_args(argc, argv, &args);
	ft_show_pid();
	signal(SIGUSR1, ft_sig_handler);
	signal(SIGUSR2, ft_sig_handler);
	i = 0;
	while (args.msg_to_send[i])
		ft_send_byte_to_pid(args.server_pid, \
			args.msg_to_send[i++], INTERVAL_US);
	ft_send_byte_to_pid(args.server_pid, 0, INTERVAL_US);
	free_x((void **)&args.msg_to_send);
	return (0);
}
