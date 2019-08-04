/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:23:40 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/04 23:18:30 by wdeltenr         ###   ########.fr       */
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

void		display_tab2(t_rooms **tab)
{
	t_links	*li;
	int		i;

	i = 0;
	while (tab[i])
	{
		printf("%s: dist=%d\n", tab[i]->name, tab[i]->d);
		li = tab[i]->links;
		while (li)
		{
			printf("%s-%s: %d\n", tab[i]->name, li->room->name, li->w);
			li = li->next;
		}
		printf("\n");
		i++;
	}
}

static void	dijkstra(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	int		i;
	int		j;

	i = 0;
	j = i;
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (((tab[i]->d + li->w < li->room->d) ||
			li->room->d == -1) && tab[i]->d != -1)
			{
				j++;
				li->room->d = tab[i]->d + li->w;
				arrange_tab(hill, tab, j, li->room->index);
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

	swap_rooms(hill, tab, 0, hill->start);
	dijkstra(hill, tab);
	find_path(tab, tab[hill->end], NULL);
	if (tab[hill->size / 2 - 1]->d == -1)
	{
		write(2, "Error no path\n", 15);
		free_hill(hill);
		return ;
	}
	paths = all_paths(hill, tab, 1);
	hill->turns = max_turns(hill, paths, 1);
	suurballe(hill, tab, paths);
}
