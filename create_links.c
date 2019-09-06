/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:44:48 by gdrion            #+#    #+#             */
/*   Updated: 2019/09/06 18:34:09 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms	*get_room_add(t_hill *hill, char *name, int size)
{
	int				left;
	int				right;
	unsigned int	hashed;

	hashed = hash(name, size);
	if (hill->rooms[hashed] && !ft_strcmp(hill->rooms[hashed]->name, name))
		return (hill->rooms[hashed]);
	left = hashed - 1;
	right = hashed + 1;
	while (left >= 0 || right < size)
	{
		if (left >= 0 && hill->rooms[left] &&
		!ft_strcmp(hill->rooms[left]->name, name))
			return (hill->rooms[left]);
		if (right < size && hill->rooms[right] &&
		!ft_strcmp(hill->rooms[right]->name, name))
			return (hill->rooms[right]);
		left--;
		right++;
	}
	return (NULL);
}

static t_links	*init_links(t_rooms *room, t_links *out)
{
	t_links	*new;

	if (!(new = malloc(sizeof(t_links))))
		return (NULL);
	new->room = room;
	new->w = 1;
	new->next = NULL;
	new->out = out;
	return (new);
}

static int		stock_links(t_rooms *room, t_links *new)
{
	t_links	*tmp;

	tmp = room->links;
	if (!tmp)
	{
		room->links = new;
		return (0);
	}
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->room->name, new->room->name))
			return (0);
		tmp = tmp->next;
	}
	if (!ft_strcmp(tmp->room->name, new->room->name))
		return (0);
	tmp->next = new;
	return (1);
}

static int		store_links2(t_rooms *room1, t_rooms *room2)
{
	t_links	*in;
	t_links	*out;

	if (!(in = init_links(room2, NULL)))
		return (0);
	if (!(out = init_links(room1, in)))
		return (0);
	in->out = out;
	stock_links(room1, in);
	stock_links(room2, out);
	//en fonction du retour du premier stock_links, ne pas appeler le deuxieme et free
	return (1);
}

int				parse_links(t_hill *hill, t_rooms **tab, char *line)
{
	t_rooms	*room1;
	t_rooms	*room2;
	char	**lines;

	if (!(lines = check_links(line)))
		return (0);
	if (!(room1 = get_room_add(hill, lines[0], hill->size)))
		return (0);
	if (!(room2 = get_room_add(hill, lines[1], hill->size)))
		return (0);
	if (!(store_links2(room1, room2)))
		return (0);
/*	free(lines[0]) YOU NEED TO FREE LINES;
	lines[0]=NULL;
	free(lines[1]);
	lines[1]=NULL;
	free(lines);
	lines=NULL;*/
	return (1);
}
