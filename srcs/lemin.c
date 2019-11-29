/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:09:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/11/28 15:57:45 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void empty_gnl(void)
{
 	char 	*empty;

	while (get_next_line(0, &empty) > 0)
		ft_strdel(&empty);
}

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
	int			ret;

	if (!(hill = create_hill()))
		return (-1);
	if (get_next_line(0, &line) != 1)
		return (free_error(hill));
	if ((hill->ants = check_ants(line)) <= 0)
	{
		ft_strdel(&line);
		while (get_next_line(0, &line) == 1)
			ft_strdel(&line);
		return (free_error(hill));
	}
	ft_strdel(&line);
	if (!(ret = parser(hill, line)) || ret == -1)
		return (free_error(hill));
	empty_gnl();
	free_hill(hill);
	return (0);
}
