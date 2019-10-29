/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:22:55 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 12:33:46 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		fix_tab(t_hill *hill, t_rooms **tab, int i)
{
	while (i < hill->size - 1)
	{
		tab[i] = tab[i + 1];
		tab[i]->index--;
		i++;
	}
	tab[i] = NULL;
	hill->size -= 1;
}

static t_links	*del(t_hill *hill, t_rooms **tab, t_links *li, t_rooms *room)
{
	t_rooms		*save;
	t_links		*tmp;

	if (room->index == START || room->index == END)
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


static t_links	*no_link(t_hill *hill, t_rooms **tab, int i)
{
	free_room(&tab[i]);
	fix_tab(hill, tab, i);
	return (NULL);
}

void			dead_end(t_hill *hill, t_rooms **tab)
{
	int			i;
	int			dead;
	t_links		*li;

	dead = 0;
	i = 0;
	while (i < hill->size - 1)
	{
		li = tab[i]->links;
		if (!li)
			li = no_link(hill, tab, i);
		while (li)
		{
			if (li->room != tab[START] && li->room != tab[END]
				&& !li->room->links->next)
			{
				dead = 1;
				li = del(hill, tab, li, li->room);
			}
			else
				li = li->next;
		}
		dead == 1 ? dead = 0 : i++;
	}
}
