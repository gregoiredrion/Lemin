/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:18:57 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/30 16:46:23 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms	**store_path(t_rooms **tab, t_rooms **path, t_rooms *room)
{
	t_links		*li;
	t_links		*save;
	int			j;

	j = 0;
	li = room->links;
	if (room->index != END)
		path[j++] = room;
	while (room->index != END && li->room != tab[END])
	{
		if (li->used && !li->opp->used)
		{
			path[j++] = li->room;
			save = li;
			li = li->room->links;
		}
		else
			li = li->next;
		if (!li)
			li = tab[-save->room->index]->links;
	}
	path[j++] = tab[END];
	path[j] = NULL;
	return (path);
}

static int		len(t_rooms **tab, t_rooms *room, t_rooms *end)
{
	t_links		*li;
	t_links		*save;
	int			len;

	len = 1;
	li = room->links;
	if (room == end)
		return (len);
	while (li->room != end)
	{
		if (li->used && !li->opp->used)
		{
			len++;
			save = li;
			li = li->room->links;
		}
		else
			li = li->next;
		if (!li)
			li = tab[-save->room->index]->links;
	}
	return (len + 1);
}

static t_rooms	**get_new_path(t_rooms **tab, t_rooms *room)
{
	t_rooms		**new_path;
	int			len_path;

	len_path = len(tab, room, tab[END]) + 1;
	if (!(new_path = ft_memalloc(sizeof(t_rooms *) * len_path)))
		return (NULL);
	new_path[len_path - 1] = NULL;
	new_path[0] = room;
	new_path = store_path(tab, new_path, room);
	return (new_path);
}

t_rooms			***all_paths(t_rooms **tab, int nb_paths)
{
	t_links		*li;
	t_rooms		***paths;
	int			i;

	i = 0;
	if (!(paths = ft_memalloc(sizeof(t_rooms **) * (nb_paths + 1))))
		return (NULL);
	paths[nb_paths] = NULL;
	li = tab[START]->links;
	while (li && i < nb_paths)
	{
		if (li->used)
			if (!(paths[i++] = get_new_path(tab, li->room)))
				return (NULL);
		li = li->next;
	}
	if (duplicate_rooms(paths) == -1)
		return (NULL);
	return (paths);
}
