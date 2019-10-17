/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupe_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:58:43 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/17 15:22:11 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_links	*push_back(t_links *li, t_links *add)
{
	t_links		*begin;

	begin = li;
	if (!li)
		return (add);
	while (li->next)
		li = li->next;
	li->next = add;
	return (begin);
}

static t_links	*clones_link(t_rooms *room, t_rooms *clone)
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
	else
	{
		while (li)
		{
			if (li->next->w == -1)
			{
				new = li->next;
				li->next = new->next;
				new->next = NULL;
				return (new);
			}
			li = li->next;
		}
		return (NULL);
	}
}

static void		set_links(t_rooms *room, t_rooms *clone)
{
	t_links		*li;
	t_links		*new;

	li = room->links;
	while (li)
	{
		if (li->w == -1)
		{
			li = li->next;
			clone->links = clones_link(room, clone);
		}
		else
		{
			if (li->opp->w != -1)
				li->opp->room = clone;
			li = li->next;
		}
	}
	if (!(new = malloc(sizeof(t_links))))
		return ;
	new->room = clone;
	new->w = 0;
	new->used = 0;
	new->next = NULL;
	new->opp = NULL;
	push_back(room->links, new);
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
	set_links(room, new);
	return (new);
}

void		dupe_rooms(t_rooms ***paths)
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
					return ;
			}
			j++;
		}
		i++;
	}
}
