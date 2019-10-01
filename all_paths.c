/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:18:57 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/01 11:29:34 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		set_links(t_rooms *room)
{
	t_links		*li;

	li = room->links;
	while (li)
	{
		if (li->used)
			li->opp->in = 1;
		else if (li->opp->used)
			li->in = 1;
		else
		{
			li->out = 1;
			li->opp->in = 1;
		}
		li = li->next;
	}
}

static void		dupe_rooms(t_rooms ***paths)
{
	int		i;
	int		j;

	i = 0;
	while (paths[i])
	{
		j = 0;
		while (paths[i][j + 1])
		{
			if (!paths[i][j]->used)
			{
				paths[i][j]->used = 1;
				set_links(paths[i][j]);
			}
			j++;
		}
		i++;
	}
}

static t_rooms	**store_paths(t_rooms **tab, t_rooms *room, t_rooms *end)
{
	t_links		*li;
	int			j;
	t_rooms		*prev;

	j = 0;
	while (room != end)
	{
		li = room->links;
		tab[j++] = room;
		while (!li->used || (prev && prev == li->room))
			li = li->next;
		prev = room;
		room = li->room;
	}
	tab[j++] = room;
	tab[j] = NULL;
	return (tab);
}

static int		len(t_rooms *room, t_rooms *end)
{
	t_links		*li;
	int			len;

	len = 1;
	li = room->links;
	if (room == end)
		return (len);
	while (li->room != end)
	{
		if (li->used && li->opp->used)
		{
			li->used = 0;
			li->opp->used = 0;
		}
		if (li->used)
		{
			len++;
			li = li->room->links;
		}
		else
			li = li->next;
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
			len_path = len(li->room, tab[hill->end]) + 1;
			if (!(tmp = ft_memalloc(sizeof(t_rooms *) * len_path)))
				return (NULL);
			tmp[len_path - 1] = NULL;
			tmp[0] = li->room;
			paths[i++] = store_paths(tmp, li->room, tab[hill->end]);
		}
		li = li->next;
	}
	dupe_rooms(paths);
	return (paths);
}
