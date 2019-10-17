/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:18:57 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/17 14:54:07 by wdeltenr         ###   ########.fr       */
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
	path[j++] = room;
	while (li->room != tab[END])
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

t_rooms			***all_paths(t_hill *hill, t_rooms **tab, int nb_paths)
{
	t_links		*li;
	t_rooms		***paths;
	t_rooms		**tmp;
	int			i;
	int			len_path;;

	i = 0;
	if (!(paths = ft_memalloc(sizeof(t_rooms **) * (nb_paths + 1))))
		return (NULL);
	paths[nb_paths] = NULL;
	li = tab[0]->links;
	while (li && i < nb_paths)
	{
		if (li->used)
		{
			len_path = len(tab, li->room, tab[hill->end]) + 1;
			if (!(tmp = ft_memalloc(sizeof(t_rooms *) * len_path)))
				return (NULL);
			tmp[len_path - 1] = NULL;
			tmp[0] = li->room;
			paths[i++] = store_path(tab, tmp, li->room);
		}
		li = li->next;
	}
	dupe_rooms(paths);
	return (paths);
}
