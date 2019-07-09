/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:23:40 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/09 22:36:24 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	swap_rooms(t_hill *hill, t_rooms **tab, int i, int room_ind)
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
}

int		arrange_tab(t_hill *hill, t_rooms **tab, int j, int room_ind)
{
	if (!tab[j])
		return 0;
	if (tab[j]->dist == -1) // Not useful imo but too tired to be sure
		swap_rooms(hill, tab, j, room_ind);
	return 1;
}

void	bad_sort(t_hill *hill, t_rooms **tab, int from, int to)
{
	int save = from;
	while (from < to)
	{
		if (tab[from]->dist > tab[from + 1]->dist)
		{
			swap_rooms(hill, tab, from, from + 1);
			from = save;
		}
		else
			from++;
	}
}

void		blablablebleble(t_hill *hill, t_rooms **tab, t_links *li, int i)
{
	int j = i;
	while (li)
	{
		if (((tab[i]->dist + li->weight< li->room->dist) ||
		li->room->dist == -1) && tab[i]->dist != -1)
		{
			j++;
			li->room->dist = tab[i]->dist + li->weight;
			arrange_tab(hill, tab, j, li->room->index);
			bad_sort(hill, tab, i, j);
		}
		li = li->next;
	}
}

void	djikstra(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	t_links	*li2;
	int		i;
	int		j;
	int		len; // Will be used to do a faster sort

	len = 0;
	i = 0;
	while (tab[i])
	{
		li = tab[i]->in;
		li2 = tab[i]->out;
		blablablebleble(hill, tab, li, i);
		blablablebleble(hill, tab, li2, i);
		i++;
	}
}

void	short_path(t_hill *hill, t_rooms **tab)
{
	swap_rooms(hill, tab, 0, hill->start);
	djikstra(hill, tab);
	display_tab(tab, 7);
	find_path(tab[hill->end]);
	if (tab[hill->size / 2 - 1]->dist == -1)
	{
		write(2, "Error no path\n", 15);
	}
	//Then find path starting from end;
	//Mais alors mettre les liens dans les deux rooms, pas sur que bonne idee
}
