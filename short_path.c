/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:23:40 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/09 14:27:22 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		affiche_vitfai(t_hill *hill, t_links *link, t_rooms *end)
{
	t_links *tmp;

	tmp = link;
	if (!tmp)
	//error
		return (-1);
	if (tmp->room == end)
	{
		printf("%s", tmp->room->name);
		return (1);
	}
	printf("%s", tmp->room->name);
	tmp = tmp->room->links;
	return (affiche_vitfai(hill, tmp, end));
}

void	arrange_tab(t_rooms **tab, int i, int room_ind)
{
	t_rooms	*tmp;

	tmp = tab[i];
	tab[i] = tab[room_ind];
	tab[room_ind] = tmp;
}

int		rearrange_tab(t_rooms **tab, int j, int room_ind)
{
	if (!tab[j])
		return 0;
	if (tab[j]->dist == -1) // Not useful imo but too tired to be sure
		arrange_tab(tab, j, room_ind);
	return 1;
}

void	bad_sort(t_rooms **tab, int from, int to)
{
	int save = from;
	while (from < to)
	{
		if (tab[from]->dist > tab[from + 1]->dist)
		{
			arrange_tab(tab, from, from + 1);
			from = save;
		}
		else
			from++;
	}
}

void	djikstra(t_rooms **tab)
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
			if ((tab[i]->dist + li->weight< li->room->dist) || li->room->dist == -1)
			{
				j++;
				li->room->dist = tab[i]->dist + li->weight;
				rearrange_tab(tab, j, li->room->index);
				len++;
				bad_sort(tab, i, j);
			}
			li = li->next;
		}

		i++;
	}
}

void	short_path(t_hill *hill, t_rooms **tab)
{
	arrange_tab(tab, 0, hill->start);
	display_tab(tab, 7);
	djikstra(tab);
	display_tab(tab, 7);
	//Then find path starting from end;
	//Mais alors mettre les liens dans les deux rooms, pas sur que bonne idee
}
