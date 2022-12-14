/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_svr_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:33:21 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/14 18:29:34 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_SVR_UTILS_H
# define MINITALK_SVR_UTILS_H
# define QUEUE_SIZE	1600

# include "../libft/libft.h"

typedef struct s_client_data
{
	pid_t	pid;
	int		count;
	char	byte;
	int		exitcount;
	char	*msg;
}	t_client_data;

typedef struct s_sig_event
{
	int		sig;
	pid_t	pid;
}	t_sig_event;

typedef struct s_sig_event_queue
{
	int			head;
	int			tail;
	int			mutex;
	t_sig_event	ar[QUEUE_SIZE];
}	t_sig_event_queue;

typedef struct s_feedback
{
	size_t	pending;
	int		queue_hi;
}	t_feedback;

void	ft_init_se_queue(void);
int		ft_is_full_se_queue(int *used);
int		ft_is_empty_se_queue(void);
void	ft_init_se_queue(void);
int		ft_push_se(t_sig_event se);
int		ft_pop_se(t_sig_event *se);
int		ft_content_is_pid(unsigned int i, void *content, void *arg);
t_list	*ft_create_node_for_pid(t_list	**lst_clients, pid_t pid);
void	ft_free_node(void *node);
void	ft_clean_pid(t_list **lst, t_list *node, char byte);
void	ft_process_sig_ev(void);

#endif