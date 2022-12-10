/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_bit_from_byte.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:24:16 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/10 14:28:52 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_utils.h"

int	ft_take_bit_from_byte(char byte, int *bit, int *count)
{
	char	mask;

	if (! count || ! bit)
		return (0);
	mask = 1 << (7 - *count);
	*bit = ((byte & mask) != 0);
	if (++*count == 8)
	{
		*count = 0;
		return (1);
	}
	return (0);
}
