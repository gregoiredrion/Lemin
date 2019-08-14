/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:22:55 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/14 22:17:28 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		fix_tab(t_hill *hill, t_rooms **tab, int i)
{
	while (i  < hill->size / 2 - 1)
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

static int	del_dead(t_hill *hill, t_rooms **tab, t_links *li, t_rooms *room)
{
	t_rooms		*save;
	t_links		*tmp;

	if (room == tab[hill->start] || room == tab[hill->end])
		return (1);
	save = li->out->room;
	if (save->links == li)
	{
		save->links = li->next;
		tmp = save->links;
	}
	else
	{
		tmp = save->links;
		while (tmp->next != li)
			tmp = tmp->next;
		tmp->next = li->next;
	}
	tab[room->index] = NULL;
	fix_tab(hill, tab, room->index);
	li->out->next = NULL;
	free(li->out);
	li->out = NULL;
	free(li);
	li = NULL;
	free(room);
	room = NULL;
	if (!save->links->next)
		return (del_dead(hill, tab, save->links->out, save));
	return (1);
}

void		dead_end(t_hill *hill, t_rooms **tab)
{
	int			i;
	t_links		*li;
	t_links		*tmp;

	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (!li->room)
				break ;
			else if (!li->room->links->next)
			{
				tmp = li;
				li = NULL;
				del_dead(hill, tab, tmp, tmp->room);
			}
			else
				li = li->next;
		}
		i++;
	}
}
