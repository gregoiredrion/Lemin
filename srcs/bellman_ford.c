/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:38:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/24 16:09:10 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		init_dists(t_rooms **tab)
{
	int		i;

	i = 1;
	while (tab[i])
	{
		tab[i]->pred = -1;
		if (tab[i]->used)
		{
			tab[i]->next->pred = -1;
			tab[i]->next->d = -1;
		}
		tab[i++]->d = -1;
	}
}

static int		update_dist(t_rooms *room)
{
	int			updated;
	t_links		*li;

	updated = 0;
	while (room)
	{
		li = room->links;
		while (li)
		{
			if (li->room->index == 0 || li->used || room->d == -1)
				;
			else if (room->d + li->w < li->room->d || li->room->d == -1)
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

void			bellman_ford(t_rooms **tab, int size)
{
	int			k;
	int			i;
	int			updated;

	k = 1;
	init_dists(tab);
	while (k < size)
	{
		i = 0;
		updated = 0;
		while (tab[i])
		{
			if (i == END)
				i++;
			if (!tab[i])
				break ;
			updated += update_dist(tab[i]);
			i++;
		}
		if (!updated)
			break ;
		k++;
	}
}
