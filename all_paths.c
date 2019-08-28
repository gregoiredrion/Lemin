/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:18:57 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/28 18:27:25 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms	**store_paths(t_rooms **tab, t_rooms *room, t_rooms *end)
{
	t_links		*li;
	int			j;

	j = 0;
	while (room != end)
	{
	//	printf("IN\n");
	//	printf("%s\n", room->name);
		li = room->links;
		tab[j++] = room;
		room->d = 0;
		while (li->w != -1)
			li = li->next;
		room = li->room;
		//display_room(room);
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
	while (li->room != end)
	{
		if (li->w == -1)
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

	i = 0;
	if (!(paths = malloc(sizeof(t_rooms ***) * nb_paths + 1)))
		return (NULL);
	paths[nb_paths] = NULL;
	li = tab[0]->links;
	while (li && i < nb_paths)
	{
		if (li->w == -1)
		{
			if (!(tmp =
			malloc(sizeof(t_rooms **) * (len(li->room, tab[hill->end]) + 1))))
				return (NULL);
			tmp[0] = li->room;
			paths[i++] = store_paths(tmp, li->room, tab[hill->end]);
		}
		li = li->next;
	}
//	display_paths(hill, paths);
//	printf("\n\n\n");
	return (paths);
}
