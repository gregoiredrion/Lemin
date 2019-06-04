/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:02:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/06/04 19:28:55 by wdeltenr         ###   ########.fr       */
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

/*
 ** (hash << 5) + hash + c == hash * 33 + c
 */

static unsigned int		fix_collision(t_rooms **rooms, int size)
{

}

static unsigned int		hash(char *str, int size)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = (hash << 5) + hash + c;
	return (hash % size);
}

void					hashmap(t_hill *anthill, t_rooms *begin)
{
	t_rooms			*save;
	unsigned int	hashed;

	save = begin;
	anthill->size *= 2;
	anthill->rooms = create_hash(anthill->size);
	while (begin)
	{
		hashed = hash(begin->name, anthill->size);
		if (!(anthill->rooms[hashed]))
			hashed = fix_collision(anthill->rooms, hashed);
		anthill->rooms[hashed] = begin;
		begin = begin->next;
	}
	//free(save);
}
