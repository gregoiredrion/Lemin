/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:22:55 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/04 17:22:40 by wdeltenr         ###   ########.fr       */
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
			hill->end--;
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
	free(li->out);
	li->out = NULL;
	free(li);
	li = NULL;
	free(room);
	room = NULL;
	if (!save->links->next)
		return (del(hill, tab, save->links->out, save));
	return (save->links->out);
}

void			dead_end(t_hill *hill, t_rooms **tab)
{
	int			i;
	t_links		*li;

	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		if (!li)
		{
			free_room(&tab[i]);
			fix_tab(hill, tab, i--);
		}
		while (li)
		{
			if (!li->room->links->next)
				li = del(hill, tab, li, li->room);
			else
				li = li->next;
		}
		i++;
	}
}
