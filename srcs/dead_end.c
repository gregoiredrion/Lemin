/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:22:55 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/23 17:23:28 by wdeltenr         ###   ########.fr       */
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

	if (room->index == hill->start || room->index == hill->end)
		return (NULL);
	save = li->opp->room;
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
	li->opp->next = NULL;
	free_room(&room);
	if (save->links && !save->links->next)
		return (del(hill, tab, save->links->opp, save));
	else if (!save->links)
		return (NULL);
	return (save->links->opp);
}

void			end_links(t_hill *hill, t_rooms **tab, t_rooms **end)
{
	t_links		*li;
	t_links		*next;
	int			i;

	li = (*end)->links;
	while (li && li->room->d == -1)
	{
		next = li->next;
		(*end)->links = next;
		fix_tab(hill, tab, li->room->index);
		li->next = NULL;
		free_room(&li->room);
		del_link(&li);
		li = next;
	}
	while (li->next)
	{
		next = li->next;
		if (next && next->room->d == -1)
		{
			li->next = next->next;
			next->next = NULL;
			fix_tab(hill, tab, next->room->index);
			free_room(&next->room);
			del_link(&next);
		}
		else
			li = li->next;
	}
	i = hill->size / 2 - 1;
	while (tab[i] && tab[i]->d == -1)
	{
		free_room(&tab[i--]);
		hill->size -= 2;
	}
}
/*
static t_links	*no_link(t_hill *hill, t_rooms **tab, int i)
{
	free_room(&tab[i]);
	fix_tab(hill, tab, i);
	return (NULL);
}*/

void			dead_end(t_hill *hill, t_rooms **tab)
{
	int			i;
	int			dead;
	t_links		*li;

	dead = 0;
	i = 0;
	while (i < hill->size / 2 - 1)
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->room != tab[hill->start]
			&& li->room != tab[hill->end]
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
