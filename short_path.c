/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:23:40 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/10 14:42:12 by wdeltenr         ###   ########.fr       */
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
	if (tab[j]->d == -1) // Not useful imo but too tired to be sure
		swap_rooms(hill, tab, j, room_ind);
	return 1;
}

void	bad_sort(t_hill *hill, t_rooms **tab, int from, int to)
{
	int save = from;
	while (from < to)
	{
		if (tab[from]->d > tab[from + 1]->d)
		{
			swap_rooms(hill, tab, from, from + 1);
			from = save;
		}
		else
			from++;
	}
}

void	djikstra(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	int		i;
	int		j;
	int		len; // Will be used to do a faster sort

	len = 0;
	i = 0;
	while (tab[i])
	{
		j = i;
		li = tab[i]->links;
		while (li)
		{
			if (((tab[i]->d + li->w < li->room->d) ||
			li->room->d == -1) && tab[i]->d != -1)
			{
				j++;
				li->room->d = tab[i]->d + li->w;
				arrange_tab(hill, tab, j, li->room->index);
				len++;
				bad_sort(hill, tab, i, j);
			}
			li = li->next;
		}
		i++;
	}
}

void	short_path(t_hill *hill, t_rooms **tab)
{
	swap_rooms(hill, tab, 0, hill->start);
	djikstra(hill, tab);
	display_tab(tab, 8);
	find_path(tab, tab[hill->end]);
	if (tab[hill->size / 2 - 1]->d == -1)
	{
		write(2, "Error no path\n", 15);
	}
	suurballe(hill, tab);
	//Then find path starting from end;
	//Mais alors mettre les liens dans les deux rooms, pas sur que bonne idee
}
