/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:44:48 by gdrion            #+#    #+#             */
/*   Updated: 2019/07/06 15:18:42 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		get_room2_id(char *line, int size, char **name)
{
	unsigned int	hashed;
	int				c;
	int				len;
	int				i;

	len = 0;
	hashed = 5381;
	while (line[len] && line[len - 1] != '-')
		len++;
	i = len;
	while (line[i])
	{
		c = line[i];
		hashed = (hashed << 5) + hashed + c;
		i++;
	}
	*name = ft_strsub(line, len, ft_strlen(line));
	if (!(*line))
		return (-1);
	return ((int)(hashed % size));
}

static int		get_room_id(char *line, int size, char **name)
{
	unsigned int	hashed;
	int				c;
	int				len;

	len = 0;
	hashed = 5381;
	while (line[len] && line[len] != '-')
	{
		c = line[len];
		hashed = (hashed << 5) + hashed + c;
		len++;
	}
	*name = ft_strndup(line, len);
	if (!(*line))
		return (-1);
	return ((int)(hashed % size));
}

static t_rooms	*get_room_add(t_hill *hill, int hash, char *name, int size)
{
	int left;
	int right;

	if (hill->rooms[hash] && !ft_strcmp(hill->rooms[hash]->name, name))
		return (hill->rooms[hash]);
	left = hash - 1;
	right = hash + 1;
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

static int			store_links(t_rooms **tab, int id1, int id2)
{
	t_links		*new;
	t_links		*tmp;

	tmp = tab[id1]->links;
	if (!(new = malloc(sizeof(t_links))))
		return (0);
	new->name = id2;
	new->weight = 1;
	new->next = NULL;
	if (!(tab[id1]->links))
		tab[id1]->links = new;
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
	int		hash_id;
	t_rooms	*room;
	char	*name;
	int		id1;
	int		id2;

	if ((hash_id = get_room_id(line, hill->size, &name)) < 0)
		return (0);
	if (!(room = get_room_add(hill, hash_id, name, hill->size)))
		return (0);
	ft_strdel(&name);
	id1 = room->index;
	if ((hash_id = get_room2_id(line, hill->size, &name)) < 0)
		return (0);
	if (!(room = get_room_add(hill, hash_id, name, hill->size)))
		return (0);
	printf("Room index = %d\n", room->index);
	if (room == tab[room->index])
		printf("Bingo !\n");
	ft_strdel(&name);
	id2 = room->index;
	store_links(tab, id1, id2);
	return (1);
}
