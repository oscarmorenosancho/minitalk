/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:46:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/14 13:36:58 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

#define INTERVAL_US	50

static void	ft_show_kill_error_n_exit(void)
{
	char	*errstr;

	ft_log_error("Kill couldn't sent an event\n");
	errstr = "The target process or process group does not exist\n";
	ft_putstr_fd(errstr, 2);
	ft_putchar_fd('\n', 2);
	exit (-1);
}

static void	ft_send_bit_to_pid(int pid, int bit, useconds_t u)
{
	int		ret;
	int		pending;
	int		queue_hi;

	if (bit)
		ret = kill(pid, SIGUSR2);
	else
		ret = kill(pid, SIGUSR1);
	pending = ft_get_feedback_pending() + 1;
	ft_set_feedback_pending(pending);
	if (ret == -1)
		ft_show_kill_error_n_exit();
	pending = ft_get_feedback_pending();
	if (pending > 0)
		usleep(u * ft_get_feedback_pending());
	queue_hi = ft_get_queue_hi();
	while (queue_hi)
		usleep(1000);
	usleep(u);
}

static void	ft_send_byte_to_pid(int pid, char byte, useconds_t u)
{
	int	counter;
	int	bit;

	counter = 0;
	while (ft_get_feedback_pending() > 0)
		usleep(u);
	if (ft_get_queue_hi() && counter > 0)
		counter--;
	while (! ft_take_bit_from_byte(byte, &bit, &counter))
		ft_send_bit_to_pid(pid, bit, u);
	ft_send_bit_to_pid(pid, bit, u);
}

static void	ft_sig_handler(int sig)
{
	(void)sig;
	ft_dec_feedback_pending();
	if (sig == SIGUSR2)
		ft_putstr_fd("Received queue in danger\n", 1);
	ft_set_queue_hi(sig == SIGUSR2);
	ft_putstr_fd("\r", 1);
	ft_putnbr_fd(ft_get_feedback_pending(), 1);
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
