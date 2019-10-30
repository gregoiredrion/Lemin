/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:49:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/30 16:46:28 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		push_back(t_links *li, t_links *add)
{
	t_links		*begin;

	begin = li;
	while (li->next)
		li = li->next;
	li->next = add;
	return (1);
}

static t_links	*get_clone_link(t_rooms *room)
{
	t_links		*new;
	t_links		*li;

	li = room->links;
	if (li->w == -1)
	{
		room->links = li->next;
		li->next = NULL;
		return (li);
	}
	while (li)
	{
		if (li->next && li->next->w == -1)
		{
			new = li->next;
			li->next = new->next;
			new->next = NULL;
		}
		li = li->next;
	}
	return (new);
}

static int		set_links(t_rooms *room, t_rooms *clone)
{
	t_links		*li;
	t_links		*new;

	li = room->links;
	while (li)
	{
		if (li->w == -1)
		{
			li = li->next;
			clone->links = get_clone_link(room);
		}
		else
		{
			if (li->opp->w != -1)
				li->opp->room = clone;
			li = li->next;
		}
	}
	if (!(new = create_link(clone, NULL)))
		return (-1);
	new->w = 0;
	return (push_back(room->links, new));
}

static t_rooms	*clone(t_rooms *room)
{
	t_rooms *new;

	if (!(new = malloc(sizeof(t_rooms))))
		return (NULL);
	if (!(new->name = ft_strdup(room->name)))
		return (NULL);
	new->ants = 0;
	new->d = -1;
	new->index = -room->index;
	new->pred = -1;
	new->used = 1;
	new->next = NULL;
	room->next = new;
	if (set_links(room, new) == -1)
		return (NULL);
	return (new);
}

int				duplicate_rooms(t_rooms ***paths)
{
	int		i;
	int		j;

	i = 0;
	while (paths[i])
	{
		j = 0;
		while (paths[i][j + 1])
		{
			if (!paths[i][j]->used)
			{
				paths[i][j]->used = 1;
				if (!(paths[i][j]->next = clone(paths[i][j])))
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}
