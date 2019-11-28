/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:02:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/11/28 15:34:33 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_rooms					**small_tab(t_hill *hill)
{
	t_rooms		**new;
	int			i;
	int			j;
	int			size;

	size = hill->size / 2;
	j = 0;
	i = 0;
	if (!size || !(new = malloc(sizeof(t_rooms *) * (size + 1))))
		return (NULL);
	new[size] = NULL;
	while (i < hill->size)
	{
		if (hill->rooms[i])
		{
			hill->rooms[i]->next = NULL;
			hill->rooms[i]->index = j;
			hill->rooms[i]->stend == -1 ? hill->end = j : 0;
			hill->rooms[i]->stend == 1 ? hill->start = j : 0;
			new[j++] = hill->rooms[i];
		}
		i++;
	}
	return (new);
}

static t_rooms			**create_hashmap(int size)
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

int						hashmap(t_hill *hill, t_rooms *begin)
{
	int			hashed;

	hill->size *= 2;
	if (!(hill->rooms = create_hashmap(hill->size)))
		return (-1);
	while (begin)
	{
		hashed = hash(begin->name, hill->size);
		if (hill->rooms[hashed])
			hashed = collision(hill->rooms, hashed, hill->size);
		hill->rooms[hashed] = begin;
		begin = begin->next;
		hill->rooms[hashed]->next = NULL;
	}
	return (1);
}
