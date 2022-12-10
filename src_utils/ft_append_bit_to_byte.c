/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_bit_to_byte.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:11:44 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/10 13:45:51 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_utils.h"

int	ft_append_bit_to_byte(int bit, char *byte, int *count)
{
	if (!byte || ! count)
		return (0);
	*byte <<= 1;
	if (bit)
		*byte |= 1;
	if (++*count == 8)
	{
		*count = 0;
		return (1);
	}
	return (0);
}
