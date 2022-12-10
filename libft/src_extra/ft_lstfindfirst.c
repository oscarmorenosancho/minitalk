/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfindfirst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:46:19 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/01 17:44:52 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

t_list	*ft_lstfindfirst(t_list *lst, \
		int (*f)(unsigned int, void *, void *), void *arg)
{
	t_list			*cur;
	unsigned int	i;

	cur = lst;
	i = 0;
	if (! f || ! arg)
		return (NULL);
	while (cur)
	{	
		if ((*f)(i, (void *)cur->content, arg))
			return (cur);
		cur = cur->next;
		i++;
	}
	return (cur);
}
