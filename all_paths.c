/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaythosemfpaths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:07:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/30 15:14:04 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//delete
void			display_paths(t_rooms *room, t_rooms *end)
{
	t_links		*li;

	if (room == end)
		return ;
	li = room->links;
	while (li->w != -1)
		li = li->next;
	printf("-%s", li->room->name);
	display_paths(li->room, end);
}

static t_rooms	**store_paths(t_rooms **tab, t_rooms *room, t_rooms *end, int i)
{
	t_links		*li;
	int			j;

	j = 0;
	while (room != end)
	{
		li = room->links;
		tab[j++] = room;
		while (li->w != -1)
			li = li->next;
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
	while (li->room != end)
	{
		if (li->w == -1)
		{
			len++;
			li = li->room->links;
		}
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
	while (li)
	{
		if (li->w == -1)
		{
			printf("%s-%s", tab[0]->name, li->room->name);
			display_paths(li->room, tab[hill->end]);
			printf("\n");
			if (!(tmp = malloc(sizeof(t_rooms **) * (len(li->room, tab[hill->end]) + 1))))
				return (NULL);
			tmp[0] = li->room;
			paths[i++] = store_paths(tmp, li->room, tab[hill->end], 1);
		}
		li = li->next;
	}
	return (paths);
}
