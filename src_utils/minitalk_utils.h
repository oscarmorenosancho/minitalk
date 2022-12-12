/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:33:21 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/12 16:32:46 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_UTILS_H
# define MINITALK_UTILS_H
# include "../libft/libft.h"

typedef struct s_client_args
{
	int		server_pid;
	char	*msg_to_send;
}	t_client_args;

typedef struct s_client_data
{
	pid_t	pid;
	int		count;
	char	byte;
	int		exitcount;
	char	*msg;
}	t_client_data;

void	ft_check_server_args(int argc, char const *argv[]);
void	ft_get_client_args(int argc, char const *argv[], t_client_args *args);
void	ft_show_pid(void);
int		ft_append_bit_to_byte(int bit, char *byte, int *count);
int		ft_take_bit_from_byte(char byte, int *bit, int *count);

#endif