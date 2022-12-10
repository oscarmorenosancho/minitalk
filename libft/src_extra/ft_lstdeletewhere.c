/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdeletewhere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:44:20 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/01 17:44:19 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

void	ft_lstdeletewhere(t_list **lst, \
		int (*is)(unsigned int, t_list *, void *), \
		void (*del)(void *), void *arg)
{
	t_list			*prev;
	t_list			*cur;
	unsigned int	i;

	prev = NULL;
	cur = *lst;
	i = 0;
	if (! is || ! arg)
		return ;
	while (cur)
	{	
		if ((*is)(i, cur, arg))
		{
			if (prev)
				prev->next = cur->next;
			else
				*lst = cur->next;
			ft_lstdelone(cur, del);
		}
		prev = cur;
		cur = cur->next;
		i++;
	}
}
