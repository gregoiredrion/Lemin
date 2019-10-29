/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:09:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 17:41:20 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		free_error(t_hill *hill)
{
	free_hill(hill);
	write(2, "Error\n", 6);
	return (-1);
}

int				main(void)
{
	char		*line;
	t_hill		*hill;

	if (!(hill = create_hill()))
		return (-1);
	if (get_next_line(0, &line) != 1)
		return (free_error(hill));
	if ((hill->ants = check_ants(line)) <= 0)
	{
		ft_strdel(&line);
		return (free_error(hill));
	}
	ft_strdel(&line);
	if (!(parser(hill, line)))
		return (free_error(hill));
	free_hill(hill);
	return (0);
}
