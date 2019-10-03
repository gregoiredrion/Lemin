/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:38:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/03 17:05:21 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	two_used(t_rooms *room, t_links *li)
{
	int		tmp;

	if (((tmp = room->in + li->w) < li->room->out || li->room->out == -1)
	&& !li->used && room->in != -1 && li->w == -1)
	{
		li->room->out = tmp;
		if (li->room->out < li->room->in || li->room->in == -1)
		{
			li->room->in = tmp;
			return (room->index);
		}
	}
	return (li->room->pred);
}

static int	one_used(t_rooms *room, t_rooms *pred, t_links *li)
{
	int		tmp;

	if (room->used)
	{
		if (!pred->used)
			return (li->room->pred);
		if (((tmp = room->out + li->w) < li->room->d || li->room->d == -1)
		&& room->out != -1 && !li->used)
		{
			li->room->d = tmp;
			return (room->index);
		}
	}
	else
	{
		if (((tmp = room->d + li->w) < li->room->in || li->room->in == -1)
		&& room->d != -1 && !li->used)
		{
			li->room->in = tmp;
			if (li->room->in < li->room->out || li->room->out == -1)
				return (room->index);
		}
	}
	return (li->room->pred);
}

static int	used_room(t_rooms *room, t_rooms *pred, t_links *li)
{
	if (room->used && li->room->used)
		return (two_used(room, li));
	else
		return (one_used(room, pred, li));
}

static int	update_dist(t_rooms *room, t_rooms *pred, int i)
{
	int			updated;
	int			tmp;
	t_links		*li;

	updated = 0;
	li = room->links;
	while (li)
	{
		if ((room->used || li->room->used) && li->room->index > 1)
		{
			tmp = li->room->pred;
			li->room->pred = used_room(room, pred, li);
			if (tmp != li->room->pred)
				updated = 1;
		}
		else if ((room->d + li->w < li->room->d || li->room->d == -1)
		&& li->room->index != 0 && !li->used && room->d != -1)
		{
			li->room->d = room->d + li->w;
			li->room->pred = i;
			updated = 1;
		}
		li = li->next;
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
	while (k < size)
	{
		i = 0;
		updated = 0;
		while (tab[i])
		{
			if (i == 1)
				i++;
			while (tab[i] && tab[i]->d == -1 && tab[i]->in == -1
			&& tab[i]->out == -1)
				i++;
			if (!tab[i])
				break ;
			updated += update_dist(tab[i], tab[tab[i]->pred], i);
			i++;
		}
		if (!updated)
			break ;
		k++;
	}
}
