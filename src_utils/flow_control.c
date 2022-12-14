/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:06:22 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/14 10:58:32 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_utils.h"

static t_feedback	g_feedback;

size_t	ft_get_feedback_pending(void)
{
	return (g_feedback.pending);
}

int	ft_get_queue_hi(void)
{
	return (g_feedback.queue_hi);
}

void	ft_set_feedback_pending(size_t val)
{
	g_feedback.pending = val;
}

void	ft_dec_feedback_pending(void)
{
	if (g_feedback.pending > 0)
		g_feedback.pending--;
}

void	ft_set_queue_hi(int value)
{
	g_feedback.queue_hi = value;
}
