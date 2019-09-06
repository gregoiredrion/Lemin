/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:57:05 by wdeltenr          #+#    #+#             */
/*   Updated: 2018/11/29 18:57:23 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_digits(long double n)
{
	int		count;

	count = 1;
	while (n >= 1)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
