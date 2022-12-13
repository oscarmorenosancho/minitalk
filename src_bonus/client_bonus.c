/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:46:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/13 18:15:04 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

#define INTERVAL_US	50

static int	g_flag;

static void	ft_send_bit_to_pid(int pid, int bit, useconds_t u)
{
	int		ret;
	char	*errstr;

	if (bit)
		ret = kill(pid, SIGUSR2);
	else
		ret = kill(pid, SIGUSR1);
	g_flag++;
	if (ret == -1)
	{
		ft_log_error("Kill couldn't sent an event\n");
		errstr = "The target process or process group does not exist\n";
		ft_putstr_fd(errstr, 2);
		ft_putchar_fd('\n', 2);
	}
	if (g_flag > 0)
		usleep(1000 * g_flag);
	usleep(u);
}

static void	ft_send_byte_to_pid(int pid, char byte, useconds_t u)
{
	int	counter;
	int	bit;

	counter = 0;
	while (! ft_take_bit_from_byte(byte, &bit, &counter))
		ft_send_bit_to_pid(pid, bit, u);
	ft_send_bit_to_pid(pid, bit, u);
}

static void	ft_sig_handler(int sig)
{
	(void)sig;
	if (g_flag > 0)
		g_flag--;
	ft_putstr_fd("\r", 1);
	ft_putnbr_fd(g_flag, 1);
	return ;
}

static void	ft_install_aknowledge(void)
{
	signal(SIGUSR1, ft_sig_handler);
	signal(SIGUSR2, ft_sig_handler);
}

int	main(int argc, char const *argv[])
{
	t_client_args	args;
	int				i;

	g_flag = 0;
	ft_get_client_args(argc, argv, &args);
	ft_show_pid();
	ft_install_aknowledge();
	i = 0;
	while (args.msg_to_send[i])
		ft_send_byte_to_pid(args.server_pid, \
			args.msg_to_send[i++], INTERVAL_US);
	ft_send_byte_to_pid(args.server_pid, 0, INTERVAL_US);
	free_x((void **)&args.msg_to_send);
	return (0);
}
