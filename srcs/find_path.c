/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:12:55 by gdrion            #+#    #+#             */
/*   Updated: 2019/10/17 18:38:44 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		check_pred(t_rooms **tab, int pred)
{
	if (pred == -1)
		return (0);
	if (pred >= 0 && !tab[pred])
		return (0);
	if (pred < 0 && !tab[-pred]->next)
		return (0);
	return (1);
}

static t_rooms	*assign_pred(t_rooms **tab, t_rooms *room)
{
	if (room->pred == -1)
		return (NULL);
	if (room->pred >= 0)
		return (tab[room->pred]);
	else
		return (tab[-room->pred]->next);
}

int				find_path(t_rooms **tab)
{
	t_links		*li;
	t_rooms		*pred;
	int			room;

	pred = tab[tab[END]->pred];
	room = END;
	if (!check_pred(tab, tab[END]->pred))
		return (0);
	while (pred)
	{
		li = pred->links;
		while (li && li->room->index != room)
			li = li->next;
		li->used = 1;
		if (li->opp)
			li->opp->w = -1;
		room = pred->index;
		pred = assign_pred(tab, pred);
	}
	return (1);
}
