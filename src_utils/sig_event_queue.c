/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_event_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:28:53 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/13 18:58:46 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_utils.h"

static t_sig_event_queue	g_queue;

void	ft_init_se_queue(void)
{
	g_queue.mutex = 0;
	g_queue.head = 0;
	g_queue.tail = QUEUE_SIZE - 1;
}

int	ft_is_full_se_queue(int *used)
{
	if (g_queue.head > g_queue.tail)
		*used = g_queue.head - g_queue.tail;
	else
		*used = QUEUE_SIZE - (g_queue.tail - g_queue.head);
	return (g_queue.head == g_queue.tail);
}

int	ft_is_empty_se_queue(void)
{
	return (g_queue.head == ((g_queue.tail + 1) % QUEUE_SIZE));
}

int	ft_push_se(t_sig_event se)
{
	int	used;

	if (! g_queue.mutex)
		g_queue.mutex = 1;
	else
		return (0);
	if (! ft_is_full_se_queue(&used))
	{
		g_queue.ar[g_queue.head].pid = se.pid;
		g_queue.ar[g_queue.head].sig = se.sig;
		g_queue.head = (g_queue.head + 1) % QUEUE_SIZE;
		g_queue.mutex = 0;
		return (1);
	}
	g_queue.mutex = 0;
	return (0);
}

int	ft_pop_se(t_sig_event *se)
{
	if (! g_queue.mutex)
		g_queue.mutex = 1;
	else
		return (0);
	if (! ft_is_empty_se_queue())
	{
		g_queue.tail = (g_queue.tail + 1) % QUEUE_SIZE;
		se->pid = g_queue.ar[g_queue.tail].pid;
		se->sig = g_queue.ar[g_queue.tail].sig;
		g_queue.mutex = 0;
		return (1);
	}
	g_queue.mutex = 0;
	return (0);
}
