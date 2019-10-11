/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:09:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/11 13:22:28 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				main(void)
{
	char		*line;
	t_hill		*anthill;

	if (!(anthill = create_anthill()))
		return (0);
	if (get_next_line(0, &line) != 1)
		return (0);
	if ((anthill->ants = check_ants(line)) <= 0)
	{
		free(line);
		return (free_error(anthill));
	}
	ft_strdel(&line);
	if (!(parser(anthill, line)))
		return (0);
	free_hill(anthill);
	return (0);
}
