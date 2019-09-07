/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:22:55 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/07 19:22:49 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		fix_tab(t_hill *hill, t_rooms **tab, int i)
{
	while (i < hill->size / 2 - 1)
	{
		tab[i] = tab[i + 1];
		tab[i]->index--;
		if (hill->end == i + 1)
			hill->end = i;
		i++;
	}
	tab[i] = NULL;
	hill->size -= 2;
}

static t_links	*del(t_hill *hill, t_rooms **tab, t_links *li, t_rooms *room)
{
	t_rooms		*save;
	t_links		*tmp;

	if (room == tab[hill->start] || room == tab[hill->end])
		return (NULL);
	save = li->out->room;
	if (save->links == li)
		save->links = li->next;
	else
	{
		tmp = save->links;
		while (tmp->next != li)
			tmp = tmp->next;
		tmp->next = li->next;
	}
	fix_tab(hill, tab, room->index);
	li->out->next = NULL;
	free_room(&room);
	if (save->links && !save->links->next)
		return (del(hill, tab, save->links->out, save));
	else if (!save->links)
		return (NULL);
	return (save->links->out);
}

static void		no_link(t_hill *hill, t_rooms **tab, int i)
{
	free_room(&tab[i]);
	fix_tab(hill, tab, i);
}

void			dead_end(t_hill *hill, t_rooms **tab)
{
	int			i;
	int			dead;
	t_links		*li;

	i = 0;
	dead = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		if (!li && i != hill->end && i != hill->start)
			no_link(hill, tab, i--);
		while (li)
		{
			if (li->room->links->room != tab[hill->start]
			&& li->room->links->room != tab[hill->end]
			&& !li->room->links->next && (dead = 1))
				li = del(hill, tab, li, li->room);
			else
				li = li->next;
		}
		if (dead == 1)
			dead = 0;
		else
			i++;
	}
}
