/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:33:21 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/13 16:10:54 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_UTILS_H
# define MINITALK_UTILS_H
# define QUEUE_SIZE	800

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

void	ft_check_server_args(int argc, char const *argv[]);
void	ft_get_client_args(int argc, char const *argv[], t_client_args *args);
void	ft_show_pid(void);
int		ft_append_bit_to_byte(int bit, char *byte, int *count);
int		ft_take_bit_from_byte(char byte, int *bit, int *count);
void	ft_init_se_queue(void);
int		ft_is_full_se_queue(void);
int		ft_is_empty_se_queue(void);
int		ft_push_se(t_sig_event se);
int		ft_pop_se(t_sig_event *se);
int		ft_content_is_pid(unsigned int i, void *content, void *arg);
t_list	*ft_create_node_for_pid(t_list	**lst_clients, pid_t pid);
void	ft_clean_pid(t_list **lst, t_list *node, char byte);
void	ft_process_sig_ev(void);

#endif