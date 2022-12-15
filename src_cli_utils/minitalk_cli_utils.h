/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_cli_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:33:21 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 14:09:21 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_CLI_UTILS_H
# define MINITALK_CLI_UTILS_H
# define QUEUE_SIZE	1600

# include "../libft/libft.h"

typedef struct s_feedback
{
	size_t	pending;
	int		queue_hi;
}	t_feedback;

size_t	ft_get_feedback_pending(void);
int		ft_get_queue_hi(void);
void	ft_set_feedback_pending(size_t val);
void	ft_dec_feedback_pending(void);
void	ft_set_queue_hi(int value);
void	ft_show_kill_error_n_exit(void);

#endif