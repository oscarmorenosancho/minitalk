/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:39:34 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/10 11:30:48 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_utils.h"

void	ft_check_server_args(int argc, char const *argv[])
{
	if (argc != 1 || ! argv)
	{
		ft_log_error("This server program does not accept any argument\n");
		exit (-1);
	}
}

void	ft_get_client_args(int argc, char const *argv[], t_client_args *args)
{
	if (argc > 3)
	{
		ft_log_error("Too many arguments given in command line\n");
		exit (-1);
	}
	if (argc < 3)
	{
		ft_log_error("This client program needs to provide 2 arguments\n");
		ft_putstr_fd("The first argument is the server PID\n", 2);
		ft_putstr_fd("The second argument is the message to send\n", 2);
		exit (-1);
	}
	args->server_pid = atoi(argv[1]);
	if (args->server_pid < 1)
	{
		ft_log_error("PID must be a positive number\n");
		exit (-1);
	}
	args->msg_to_send = ft_strdup(argv[2]);
	if (! args->msg_to_send)
	{
		ft_log_error("malloc failed when duplicating message\n");
		exit (-1);
	}
}
