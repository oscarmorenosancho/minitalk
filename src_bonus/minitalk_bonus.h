/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:49:06 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 17:10:39 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../src_utils/minitalk_utils.h"

void	ft_send_byte_to_pid(int pid, char byte, useconds_t u);
void	ft_send_n_crc_to_pid(char *crc, int pid, char byte, useconds_t u);

#endif