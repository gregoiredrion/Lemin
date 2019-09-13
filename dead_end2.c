/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:12:23 by gdrion            #+#    #+#             */
/*   Updated: 2019/09/13 15:52:50 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		del_dead_links(t_rooms *room)
{
	t_links		*li;
	t_links		*begin;
	t_links		*tmp;

	li = room->links;
	begin = li;
	while (li)
	{
		tmp = li->next;
		if (li->room->d == -1)
		{
			if (begin == li)
				begin = tmp;
			del_link(&li);
		}
		li = tmp;
	}
	room->links = begin;
}

int			del_unused_rooms(t_rooms **tab)
{
	int			i;
	int			j;

	i = 0;
	while (tab[i])
	{
		if (tab[i]->d == -1)
		{
			j = i;
			while (tab[i])
				free_room(&tab[i++]);
		}
		else
			i++;
	}
	return ((i - j ) * 2);
}

t_rooms		*del_and_check_next(t_rooms *room)
{
	t_rooms		*next;
	t_links		*li;
	t_links		*out;
	t_links		*prev;
	int			check;

	check = 0;
	out = room->links->out;
	next = room->links->room;
	li = next->links;
	prev = NULL;
	while (li)
	{
		if (li == out)
		{
			(prev == NULL) ? next->links = li->next : li->next;
			if (prev == NULL)
				next->links = li->next;
			else
				prev = li->next;
			del_link(&li);
		}
		prev = li;
		li = li->next;
		check++;
	}
	return (check > 2 ? NULL : next);
}

int			del_deadends(t_hill *h, t_rooms **tab, t_rooms *room)
{
	t_rooms		*next;
	int			n;

	n = 0;
	while (room)
	{
		next = del_and_check_next(room);
		free_room(&room);
		room = next;
		n++;
	}
	return (n);
}

void		dead_end2(t_hill *hill, t_rooms **tab) //tab use if in hill alreayd ?
{
	int			i;
	t_links		*li;

	del_dead_links(tab[hill->end]);
	hill->size = del_unused_rooms(tab);
	exit(1);
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->room->index != hill->end && li->room->index != hill->start
			&& !li->room->links->next)
				i -= del_deadends(hill, tab, li->room);
		}
		i++; // Car del_deadends decremente de un de plus;
	}
	exit(1);
}
