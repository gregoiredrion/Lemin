/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:12:55 by gdrion            #+#    #+#             */
/*   Updated: 2019/07/09 18:38:04 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	find_path(t_rooms* room)
{
	t_links	*li;
	t_links	*save;

	if (room->index == 0)
		return (1);
	save = room->out;
	if (save)
		li = save->next;
	else
		return (0);
	while (li)
	{
		if (li->room->dist < save->room->dist)
			save = li;
		li = li->next;
	}
	if (!find_path(save->room))
	{
		return (0);
	}
	printf("L%s-%s\n", save->room->name, room->name);
	return (1);
}
