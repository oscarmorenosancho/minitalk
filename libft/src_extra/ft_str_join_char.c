/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_join_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:38:36 by omoreno-          #+#    #+#             */
/*   Updated: 2022/12/15 18:23:31 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

char	*ft_str_join_char(char **s1, char c, size_t *len)
{
	size_t	len1;
	size_t	tot_len;
	size_t	s1_len_cp;
	char	*buf;

	len1 = 0;
	tot_len = 0;
	s1_len_cp = 0;
	if (s1)
		len1 = ft_strlen_x(*s1);
	tot_len = len1 + 1;
	buf = (char *)malloc(tot_len + 1);
	if (buf)
	{
		if (len1 > 0)
			s1_len_cp = ft_strncpy_x(buf, *s1, len1);
		buf[s1_len_cp] = c;
		buf[tot_len] = 0;
		free_x((void **)s1);
	}
	if (len)
		*len = tot_len;
	return (buf);
}
