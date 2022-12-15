/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_server_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:42:31 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 17:10:18 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "../src_cli_utils/minitalk_cli_utils.h"

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

void	ft_send_byte_to_pid(int pid, char byte, useconds_t u)
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

void	ft_send_n_crc_to_pid(char *crc, int pid, char byte, useconds_t u)
{
	ft_crc(crc, byte);
	ft_send_byte_to_pid(pid, byte, u);
}
