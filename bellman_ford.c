/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:38:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/15 20:41:35 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	update_dist(t_rooms *room, int i)
{
	int			updated;
	int			tmp;
	t_links		*li;

	updated = 0;
	while (room)
	{
		li = room->links;
		while (li)
		{
			if ((room->d + li->w < li->room->d || li->room->d == -1)
			&& li->room->index != 0 && !li->used && room->d != -1)
			{
				li->room->d = room->d + li->w;
				li->room->pred = room->index;
				updated = 1;
			}
			li = li->next;
		}
		room = room->next;
	}
	return (updated);
}

void		bellman_ford(t_rooms **tab, int size)
{
	int			k;
	int			i;
	int			updated;

	k = 1;
	init_dists(tab);
	while (k++ < size)
	{
		i = 0;
		updated = 0;
		while (tab[i])
		{
			if (i == 1)
				i++;
//			while (tab[i] && tab[i]->d == -1)
//				i++;
			if (!tab[i])
				break ;
			updated += update_dist(tab[i], i);
			i++;
		}
		if (!updated)
			break ;
	}
}
