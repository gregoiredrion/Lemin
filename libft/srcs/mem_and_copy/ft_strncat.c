/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 09:38:44 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/03 15:07:54 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t slen_1;

	slen_1 = ft_strlen(s1);
	while (n-- && *s2)
		s1[slen_1++] = *s2++;
	s1[slen_1] = '\0';
	return (s1);
}