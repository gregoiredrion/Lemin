/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:02:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/06 16:08:38 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms			**create_hash(int size)
{
	t_rooms		**hashmap;
	int			i;

	i = 0;
	if (!(hashmap = malloc(sizeof(t_rooms *) * size)))
		return (NULL);
	while (i < size)
		hashmap[i++] = NULL;
	return (hashmap);
}

static unsigned int		collision(t_rooms **rooms, unsigned int hash, int size)
{
	int		left;
	int		right;

	left = hash - 1;
	right = hash + 1;
	while (left >= 0 || right < size)
	{
		if (right < size && !rooms[right])
			return (right);
		if (left >= 0 && !rooms[left])
			return (left);
		left--;
		right++;
	}
	return (right);
}

/*
** (hash << 5) + hash + c == hash * 33 + c
*/

unsigned int			hash(char *str, int size)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = (hash << 5) + hash + c;
	return (hash % size);
}

int						hashmap(t_hill *anthill, t_rooms *begin)
{
	t_rooms		*save;
	int			hashed;

	save = begin;
	anthill->size *= 2;
	if (!(anthill->rooms = create_hash(anthill->size)))
		return (0);
	while (begin)
	{
		hashed = hash(begin->name, anthill->size);
		if (anthill->rooms[hashed])
			hashed = collision(anthill->rooms, hashed, anthill->size);
		anthill->rooms[hashed] = begin;
		begin = begin->next;
	}
	return (1);
}

void					from_map_to_tab(t_hill *hill, t_rooms **tab)
{
	t_rooms		**tmp_tab;

	tmp_tab = hill->rooms;
	ft_memdel((void**)tmp_tab);
	hill->rooms = tab;
	//hill->size /= 2;
}


