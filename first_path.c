/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:23:40 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/18 18:26:44 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		swap_rooms(t_hill *hill, t_rooms **tab, int i, int room_ind)
{
	t_rooms	*tmp;

	tmp = tab[i];
	tab[i] = tab[room_ind];
	tab[room_ind] = tmp;
	tab[i]->index = i;
	tab[room_ind]->index = room_ind;
	if (tab[i]->stend == -1)
		hill->end = i;
	else if (tab[room_ind]->stend == -1)
		hill->end = room_ind;
	if (tab[i]->stend == 1)
		hill->start = i;
	else if (tab[room_ind]->stend == 1)
		hill->start = room_ind;
}

int				first_path(t_hill *hill, t_rooms **tab)
{
	t_rooms		***paths;

	if (!ft_strcmp(tab[hill->start]->name, tab[hill->end]->name))
		return (1);
	swap_rooms(hill, tab, 0, hill->start);
	swap_rooms(hill, tab, 1, hill->end);
//	if (bfs(hill) == -1)
//		return (-1);
	bellman_ford(tab, hill->size);
	if (!find_path(tab))
		return (0);
	end_links(hill, tab, &tab[hill->end]);
	dead_end(hill, tab); //tres moche donc a verif
	tab[hill->start]->ants = hill->ants;
	tab[hill->end]->ants = hill->ants;
	paths = all_paths(hill, tab, 1);//protect it
	hill->turns = max_turns(hill, paths, 1);
	if (suurballe(hill, tab, paths) == -1)
		return (-1);
	return (1);
}
