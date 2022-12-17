/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:09:03 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 14:09:29 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_cli_utils.h"

void	ft_show_kill_error_n_exit(void)
{
	char	*errstr;

	ft_log_error("Kill couldn't sent an event\n");
	errstr = "The target process or process group does not exist\n";
	ft_putstr_fd(errstr, 2);
	ft_putchar_fd('\n', 2);
	exit (-1);
}
