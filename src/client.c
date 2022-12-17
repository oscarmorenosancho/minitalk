/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:46:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/17 11:21:28 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "../src_cli_utils/minitalk_cli_utils.h"
#define INTERVAL_US	50

int	main(int argc, char const *argv[])
{
	t_client_args	args;
	int				i;
	char			crc;

	ft_get_client_args(argc, argv, &args);
	ft_show_pid();
	i = 0;
	crc = 0;
	while (args.msg_to_send[i])
		ft_send_n_crc_to_pid(&crc, args.server_pid, \
			args.msg_to_send[i++], INTERVAL_US);
	if (crc == 0)
		crc = 1;
	ft_send_byte_to_pid(args.server_pid, crc, INTERVAL_US);
	ft_send_byte_to_pid(args.server_pid, 0, INTERVAL_US);
	free_x((void **)&args.msg_to_send);
	return (0);
}
