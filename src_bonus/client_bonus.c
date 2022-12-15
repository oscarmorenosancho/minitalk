/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:46:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 17:36:39 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "../src_cli_utils/minitalk_cli_utils.h"

#define INTERVAL_US	50

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
	char			crc;

	ft_set_feedback_pending(0);
	ft_get_client_args(argc, argv, &args);
	ft_show_pid();
	signal(SIGUSR1, ft_sig_handler);
	signal(SIGUSR2, ft_sig_handler);
	i = 0;
	crc = 0;
	while (args.msg_to_send[i])
		ft_send_n_crc_to_pid(&crc, args.server_pid, \
			args.msg_to_send[i++], INTERVAL_US);
	ft_send_byte_to_pid(args.server_pid, 0, INTERVAL_US);
	free_x((void **)&args.msg_to_send);
	return (0);
}
