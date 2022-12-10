/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdeletenode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:10:36 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/01 17:44:07 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

static int	ft_eqnode(unsigned int i, t_list *lst, void *lst2)
{
	if (i >= 0)
		return (lst == lst2);
	return (0);
}

void	ft_lstdeletenode(t_list **lst, t_list *node)
{
	ft_lstdeletewhere(lst, &ft_eqnode, &free, node);
}
