/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:32:01 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 12:42:03 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				free_error(t_hill *hill)
{
	free_hill(hill);
	write(2, "Error\n", 6);
	return (0);
}

void			del_link(t_links **link)
{
	t_links	*li;

	li = *link;
	li->room = NULL;
	li->w = 0;
	li->next = NULL;
	li->opp = NULL;
	ft_memdel((void **)link);
}

void			free_links(t_links *links)
{
	t_links *tmp;

	while (links)
	{
		tmp = links->next;
		del_link(&links);
		links = tmp;
	}
}

void			free_room(t_rooms **r)
{
	t_rooms	*room;

	room = *r;
	ft_strdel(&(room->name));
	room->d = 0;
	room->index = 0;
	room->ants = 0;
	room->x = 0;
	room->y = 0;
	room->stend = 0;
	free_links(room->links);
	room->links = NULL;
	if (room->next)
		(free_room(&room->next));
	room->next = NULL;
	ft_memdel((void **)r);
}

void			free_hill(t_hill *hill)
{
	int		i;
	t_rooms	**tab;

	i = 0;
	tab = hill->rooms;
	while (i < hill->size && tab)
	{
		if (tab[i])
		{
			free_room(&tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	hill->rooms = NULL;
	hill->start = 0;
	hill->end = 0;
	hill->ants = 0;
	hill->size = 0;
	hill->turns = 0;
	hill->max_paths = 0;
	ft_memdel((void **)&tab);
	ft_memdel((void **)&hill);
}