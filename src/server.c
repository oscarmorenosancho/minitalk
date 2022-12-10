/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:56 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/10 15:10:17 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_handler(int sig)
{
	static char	byte;
	static int	count;
	int			res;

	if (sig == SIGUSR2)
		res = ft_append_bit_to_byte(1, &byte, &count);
	else
		res = ft_append_bit_to_byte(0, &byte, &count);
	if (res)
		ft_putchar_fd(byte, 1);
}

int	main(int argc, char const *argv[])
{
	ft_check_server_args(argc, argv);
	ft_show_pid();
	signal(SIGUSR1, &ft_handler);
	signal(SIGUSR2, &ft_handler);
	ft_putstr_fd("Waiting for message from client...\n", 1);
	while (1)
		pause();
}
