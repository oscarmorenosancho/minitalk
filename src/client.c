/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:46:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 14:11:35 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "../src_cli_utils/minitalk_cli_utils.h"
#define INTERVAL_US	50

static void	ft_send_bit_to_pid(int pid, int bit, useconds_t u)
{
	int		ret;

	if (bit)
		ret = kill(pid, SIGUSR2);
	else
		ret = kill(pid, SIGUSR1);
	if (ret == -1)
		ft_show_kill_error_n_exit();
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

int	main(int argc, char const *argv[])
{
	t_client_args	args;
	int				i;

	ft_get_client_args(argc, argv, &args);
	ft_show_pid();
	i = 0;
	while (args.msg_to_send[i])
		ft_send_byte_to_pid(args.server_pid, \
			args.msg_to_send[i++], INTERVAL_US);
	ft_send_byte_to_pid(args.server_pid, 0, INTERVAL_US);
	free_x((void **)&args.msg_to_send);
	return (0);
}
