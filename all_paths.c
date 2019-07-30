/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaythosemfpaths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:07:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/29 20:16:01 by gdrion           ###   ########.fr       */
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

	if (room == end)
	{
		tab[i] = end;
		return (tab);
	}
	li = room->links;
	while (li->w != -1)
		li = li->next;
	tab[i++] = li->room;
	return (store_paths(tab, li->room, end, i));
}

static void		new_dists(t_hill *hill, t_rooms **tab)
{
	t_links		*li;
	t_links		*tmp;
	t_rooms		*save;
	t_rooms		*prev;

	li = tab[0]->links;
	while (li)
	{
		tmp = li;
		if (tmp->w == -1)
		{
			save = tmp->room;
			prev = tab[0];
			while (tmp->room != tab[hill->end])
			{
				tmp->room->d = prev->d + 1;
				prev = tmp->room;
				tmp = prev->links;
				while (tmp->w != -1)
					tmp = tmp->next;
			}
			save->d = prev->d;
		}
		li = li->next;
	}
}

void			all_paths(t_hill *hill, t_rooms **tab, int nb_paths)
{
	t_links		*li;
	t_rooms		***paths;
	t_rooms		**tmp;
	int			i;

	i = 0;
	if (!(paths = malloc(sizeof(t_rooms ***) * nb_paths + 1)))
		//write error ?
		return ;
	paths[nb_paths] = NULL;
	new_dists(hill, tab);
	sort_start(tab[0]);
	li = tab[0]->links;
	while (li)
	{
		if (li->w == -1)
		{
			//printf("%s-%s", tab[0]->name, li->room->name);
			//display_paths(li->room, tab[hill->end]);
			//printf("\n");
			if (!(tmp = malloc(sizeof(t_rooms **) * (li->room->d + 1))))
				//write error ?
				return ;
			tmp[0] = li->room;
			paths[i++] = store_paths(tmp, li->room, tab[hill->end], 1);
		}
		li = li->next;
	}
	tab[hill->start]->ants = hill->ants;
	tab[hill->end]->ants = hill->ants;
	move_ants(hill, paths, tab);
}
