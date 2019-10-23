/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:44:48 by gdrion            #+#    #+#             */
/*   Updated: 2019/10/23 17:21:54 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms	*get_room(t_hill *hill, char *name, int size)
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

t_links			*create_link(t_rooms *room, t_links *opp)
{
	t_links	*new;

	if (!(new = malloc(sizeof(t_links))))
		return (NULL);
	new->room = room;
	new->w = 1;
	new->used = 0;
	new->next = NULL;
	new->opp = opp;
	return (new);
}

static int		stock_links(t_rooms *room, t_links *new)
{
	t_links	*tmp;

	tmp = room->links;
	if (!tmp)
	{
		room->links = new;
		return (1);
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

static int		store_links(t_rooms *room1, t_rooms *room2)
{
	t_links	*in;
	t_links	*opp;

	if (!(in = create_link(room2, NULL)))
		return (-1);
	if (!(opp = create_link(room1, in)))
		return (-1);
	in->opp = opp;
	if (!(stock_links(room1, in)) || !(stock_links(room2, opp)))
	{
		free_links(in);
		free_links(opp);
		return (0);
	}
	return (1);
}

int				parse_links(t_hill *hill,char *line)
{
	t_rooms	*room1;
	t_rooms	*room2;
	char	**lines;
	int		ret;
	int		i;

	i = 0;
	if (!(lines = check_links(line)))
		return (0);
	if (!(room1 = get_room(hill, lines[0], hill->size)))
		return (0);
	if (!(room2 = get_room(hill, lines[1], hill->size)))
		return (0);
	if ((ret = store_links(room1, room2) != 1))
		return (ret);
	while (lines[i])
		ft_strdel(&lines[i++]);
	ft_memdel((void **)lines);
	return (1);
}
