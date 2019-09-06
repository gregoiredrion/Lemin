/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:09:33 by gdrion            #+#    #+#             */
/*   Updated: 2019/09/04 18:32:19 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		delete_unused(t_rooms *start)
{
	t_links		*li;
	t_links		*tmp;
	t_links		*prev;

	li = start->links;
	prev = NULL;
	while (li)
	{
		if (li->w != -1)
		{
			tmp = li;
			li = li->next;
			if (!prev)
				start->links = li;
			else
				prev->next = li;
			tmp->next = NULL;
			free(tmp);
			tmp = NULL;
		}
		else
		{
			prev = li;
			li = li->next;
		}
	}
}

static void		swap_links(t_links *li, t_links *next, t_links *prev)
{
	t_links		*tmp;

	tmp = li;
	li = next;
	next = tmp;
	next->next = li->next;
	li->next = next;
	if (prev)
		prev->next = li;
}

void			sort_start(t_rooms *start)
{
	t_links		*next;
	t_links		*prev;
	t_links		*li;
	t_links		*last;

	last = NULL;
	delete_unused(start);
	li = start->links;
	while (start->links->next != last)
	{
		prev = NULL;
		li = start->links;
		while (li->next != last)
		{
			next = li->next;
			if (li->room->d > next->room->d)
			{
				swap_links(li, next, prev);
				if (!prev)
					start->links = next;
				prev = next;
			}
			else
				li = next;
		}
		last = li;
	}
}
