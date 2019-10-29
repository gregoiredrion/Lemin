/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:45:10 by gdrion            #+#    #+#             */
/*   Updated: 2019/10/29 10:55:28 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*join_and_free(char *buf, char *conv)
{
	char *new;

	if (!buf || !conv)
		return (NULL);
	if (!(new = ft_strjoin(buf, conv)))
		return (NULL);
	ft_strdel(&buf);
	ft_strdel(&conv);
	return (new);
}

static int	whatever(char *buf, t_flags *f, va_list ap, int a)
{
	int count;

	if (a == 1)
	{
		ft_putstrn(buf, ft_strlen_info(buf, f->info1));
		count = (int)ft_strlen_info(buf, f->info1);
		va_end(ap);
		ft_strdel(&buf);
		free(f);
		return (count);
	}
	f->info1 += f->info2 - 1;
	init_flags(f);
	f = NULL;
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	char	*buf;
	char	*conv;
	t_flags	*flags;

	flags = NULL;
	if (!format || !(flags = ft_create_struct(flags))
		|| !(buf = ft_strnew(0)))
		return (-1);
	(i = -1) ? va_start(ap, format) : 1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i += fill_incr(format + i, flags);
			if (!(conv = choose_conv(ap, flags)) ||
			!(buf = join_regarding_bz(buf, flags->info1, conv, flags->info2)))
				return (-1);
			whatever(buf, flags, ap, 0);
		}
		else if (format[i] != '\0' && format[i] != '%')
			if (!(buf = ft_buf_char(buf, format[i], 1, flags->info1)))
				return (-1);
	}
	return (whatever(buf, flags, ap, 1));
}
