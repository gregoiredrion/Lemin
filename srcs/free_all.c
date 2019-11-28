/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:32:01 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/11/28 13:33:30 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			free_paths(t_rooms ***paths)
{
	int		i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void			del_link(t_links **link)
{
	(*link)->room = NULL;
	(*link)->w = 0;
	(*link)->next = NULL;
	(*link)->opp = NULL;
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
	if (room->name)
		ft_strdel(&(room->name));
	room->d = 0;
	room->index = 0;
	room->ants = 0;
	room->x = 0;
	room->y = 0;
	room->stend = 0;
	if (room->links)
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
