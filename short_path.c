/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:23:40 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/11 13:48:26 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		swap_rooms(t_hill *hill, t_rooms **tab, int i, int room_ind)
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

static int	arrange_tab(t_hill *hill, t_rooms **tab, int j, int room_ind)
{
	if (!tab[j])
		return (0);
	if (tab[j]->d == -1)
		swap_rooms(hill, tab, j, room_ind);
	return (1);
}

static void	dijkstra_sort(t_hill *hill, t_rooms **tab, t_rooms *end)
{
	t_links	*li;
	int		i;
	int		j;

	i = 0;
	j = i;
	while (tab[i])
	{
		if (i == hill->end && !tab[++i])
			break ;
		li = tab[i]->links;
		while (li)
		{
			if (((tab[i]->d + li->w < li->room->d) ||
			li->room->d == -1) && tab[i]->d != -1)
			{
				li->room->d = tab[i]->d + li->w;
				arrange_tab(hill, tab, ++j, li->room->index);
			}
			li = li->next;
		}
		q_sort(hill, tab, i, j);
		i++;
	}
}

void		short_path(t_hill *hill, t_rooms **tab)
{
	t_rooms		***paths;

	if (!ft_strcmp(tab[hill->start]->name, tab[hill->end]->name))
		return ;
	swap_rooms(hill, tab, 0, hill->start);
	swap_rooms(hill, tab, 1, hill->end);
	if (!bfs(hill))
	{
		write(2, "Error\n", 15);
		return ;
	}
	end_links(hill, tab, &tab[hill->end]);
	dead_end(hill, tab);
	tab[hill->start]->ants = hill->ants;
	tab[hill->end]->ants = hill->ants;
	paths = all_paths(hill, tab, 1);
	hill->turns = max_turns(hill, paths, 1);
	suurballe(hill, tab, paths);
}
