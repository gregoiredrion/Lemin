/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:09:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/17 18:24:03 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				main(void)
{
	char		*line;
	t_hill		*hill;

	if (!(hill = create_hill()))
		return (0);
	if (get_next_line(0, &line) != 1)
		return (0);
	if ((hill->ants = check_ants(line)) <= 0)
	{
		free(line);
		return (free_error(hill));
	}
	ft_strdel(&line);
	if (!(parser(hill, line)))
		return (0);
	free_hill(hill);
	return (0);
}
