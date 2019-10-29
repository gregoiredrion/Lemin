/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:42 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 11:50:50 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		max_paths(t_rooms **tab)
{
	int			start;
	int			end;
	t_links		*tmp;

	start = 0;
	end = 0;
	tmp = tab[START]->links;
	while (tmp)
	{
		tmp = tmp->next;
		start++;
	}
	tmp = tab[END]->links;
	while (tmp)
	{
		tmp = tmp->next;
		end++;
	}
	if (end < start)
		return (end);
	return (start);
}

static void		swap_rooms(t_rooms **tab, int i, int room_ind)
{
	t_rooms	*tmp;

	tmp = tab[i];
	tab[i] = tab[room_ind];
	tab[room_ind] = tmp;
	tab[i]->index = i;
	tab[room_ind]->index = room_ind;
}

int				prep_suurballe(t_hill *hill, t_rooms **tab)
{
	if (!ft_strcmp(tab[START]->name, tab[END]->name))
		return (1);
	swap_rooms(tab, START, hill->start);
	swap_rooms(tab, END, hill->end);
	dead_end(hill, tab); //tres moche donc a verif
	hill->max_paths = max_paths(tab);
	tab[START]->ants = hill->ants;
	tab[END]->ants = hill->ants;
	if (suurballe(hill, tab) == -1)
		return (-1);
	return (1);
}
