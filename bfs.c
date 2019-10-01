/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:36:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/19 15:39:35 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		path(t_hill *hill)
{
	t_rooms		**tab;
	t_rooms		*room;
	t_links		*li;
	t_links		*save;

	tab = hill->rooms;
	room = tab[hill->end];
	while (room->index != 0)
	{
		li = room->links;
		while (li)
		{
			if (room->d == li->room->d + 1)
				break ;
			li = li->next;
		}
		li->opp->used = 1;
		li->w = -1;
		room = li->room;
	}
}

int				bfs(t_hill *hill)
{
	t_links		*li;
	t_rooms		**queue;
	int			i;
	int			j;

	i = 0;
	if (!(queue = ft_memalloc(sizeof(t_rooms *) * (hill->size * 2))))
		return (0);
	queue[i] = hill->rooms[0];
	j = 1;
	while (queue[i])
	{
		li = queue[i]->links;
		while (li)
		{
			if (li->room->d == -1 && li->w != -1)
			{
				li->room->d = queue[i]->d + 1;
				queue[j++] = li->room;
			}
			li = li->next;
		}
		i++;
	}
	free(queue);
	path(hill);
	return (1);
}
