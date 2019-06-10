/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:44:48 by gdrion            #+#    #+#             */
/*   Updated: 2019/06/10 19:32:59 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_room_id(char *line, int size, char **name)
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

t_rooms	*get_room_add(t_hill *hill, int hash, char *name, int size)
{
	int left;
	int right;

	if (hill->rooms[hash] && !ft_strcmp(hill->rooms[hash]->name, name))
		return (hill->rooms[hash]);
	left = hash - 1;
	right = hash + 1;
	while (left >= 0 || right < size)
	{
		printf("Boucle\n");
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

int		parse_links(t_hill *hill, t_rooms **tab, char *line)
{
	int		h_id;
	t_rooms	*room;
	char	*name;

	if (!(h_id = get_room_id(line, hill->size, &name)))
		return (0);
	printf ("Room '%s' has id '%d'\n", name, h_id);
	if (!(get_room_add(hill, h_id, name, hill->size)))
		return (0);
	ft_strdel(&name);
	return (1);
}
