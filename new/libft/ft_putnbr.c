/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:36:16 by wdeltenr          #+#    #+#             */
/*   Updated: 2018/10/18 11:51:13 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(intmax_t n)
{
	if (n == -9223372036854775807 - 1)
	{
		write(1, "-9", 2);
		n = 223372036854775808;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (9 < n)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
	if (n >= 0 && n <= 9)
		ft_putchar(n + 48);
}