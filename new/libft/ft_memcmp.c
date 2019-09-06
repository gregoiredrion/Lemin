/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:42:02 by wdeltenr          #+#    #+#             */
/*   Updated: 2018/07/01 20:33:51 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_2;
	unsigned char	*s2_2;

	s1_2 = (unsigned char *)s1;
	s2_2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (*s1_2 != *s2_2)
			return (s1_2[i] - s2_2[i]);
		s1_2++;
		s2_2++;
	}
	return (0);
}
