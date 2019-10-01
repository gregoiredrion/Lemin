/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:37:24 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/01 16:24:34 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:38:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/01 15:37:21 by wdeltenr         ###   ########.fr       */
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

void		bellman_ford(t_rooms **tab, int size)
{
	t_links		*li;
	int			k;
	int			i;
	int			check;

	k = 1;
	init_dists(tab);
	while (k < size)
	{
		check = 0;
		i = 0;
		while (tab[i])
		{
			if (i == 1)
				i++;
			while (tab[i] && tab[i]->d == -1 && tab[i]->in == -1 && tab[i]->out == -1)
				i++;
			if (!tab[i])
				break ;
			li = tab[i]->links;
			while (li)
			{
				if ((tab[i]->used || li->room->used) && li->room->index > 1)
					li->room->pred = used_room(tab[i], tab[tab[i]->pred], li);
				else if ((tab[i]->d + li->w < li->room->d || li->room->d == -1)
				&& li->room->index > 0 && !li->used && tab[i]->d != -1)
				{
					li->room->d = tab[i]->d + li->w;
					li->room->pred = i;
					check = 1;
				}
				li = li->next;
			}
			i++;
		}
	//	display_tab2(tab);
	//	if (!check)
	//		break ;
		k++;
	}
//	display_room(tab[463]);
//	display_room(tab[785]);
}
