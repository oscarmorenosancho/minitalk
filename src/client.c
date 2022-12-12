/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:46:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/12 17:34:48 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_bit_to_pid(int pid, int bit, useconds_t u)
{
	if (bit)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
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
	i = 0;
	while (args.msg_to_send[i])
		ft_send_byte_to_pid(args.server_pid, args.msg_to_send[i++], 1000);
	free_x((void **)&args.msg_to_send);
	return (0);
}
