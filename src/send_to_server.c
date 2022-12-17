/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:42:31 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 17:11:18 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "../src_cli_utils/minitalk_cli_utils.h"

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

void	ft_send_byte_to_pid(int pid, char byte, useconds_t u)
{
	int	counter;
	int	bit;

	counter = 0;
	while (! ft_take_bit_from_byte(byte, &bit, &counter))
		ft_send_bit_to_pid(pid, bit, u);
	ft_send_bit_to_pid(pid, bit, u);
}

void	ft_send_n_crc_to_pid(char *crc, int pid, char byte, useconds_t u)
{
	ft_crc(crc, byte);
	ft_send_byte_to_pid(pid, byte, u);
}
