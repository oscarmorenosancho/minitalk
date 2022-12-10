/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstevery.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 10:58:24 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/01 17:44:34 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

int	ft_lstevery(t_list *lst, int (*f)(void *, void *), void *arg)
{
	t_list	*cur;
	int		ok;

	cur = lst;
	ok = 1;
	if (f)
	{
		while (cur && ok)
		{	
			ok = (*f)((void *)cur->content, arg);
			cur = cur->next;
		}
	}
	return (ok);
}
