/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:44:48 by gdrion            #+#    #+#             */
/*   Updated: 2019/07/09 18:34:18 by gdrion           ###   ########.fr       */
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

static int		store_ins(t_rooms **tab, int id1, t_rooms *room)
{
	t_links		*new;
	t_links		*tmp;

	tmp = tab[id1]->in;
	if (!(new = malloc(sizeof(t_links))))
		return (0);
	new->room = room;
	new->weight = 1;
	new->next = NULL;
	if (!(tab[id1]->in))
		tab[id1]->in = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

static int		store_outs(t_rooms **tab, int id1, t_rooms *room)
{
	t_links		*new;
	t_links		*tmp;

	tmp = tab[id1]->out;
	if (!(new = malloc(sizeof(t_links))))
		return (0);
	new->room = room;
	new->weight = 1;
	new->next = NULL;
	if (!(tab[id1]->out))
		tab[id1]->out = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

int				parse_links(t_hill *hill, t_rooms **tab, char *line)
{
	t_rooms	*room1;
	t_rooms	*room2;
	char	**lines;
	int		id1;
	int		id2;

	lines = ft_strsplit(line, '-');
	if (!(room1 = get_room_add(hill, lines[0], hill->size)))
		return (0);
	id1 = room1->index;
	if (!(room2 = get_room_add(hill, lines[1], hill->size)))
		return (0);
	id2 = room2->index;
	store_outs(tab, id2, room1);
	store_ins(tab, id1, room2);
	free(lines[0]);
	lines[0]=NULL;
	free(lines[1]);
	lines[1]=NULL;
	free(lines);
	lines=NULL;
	return (1);
}
