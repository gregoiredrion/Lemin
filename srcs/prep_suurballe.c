/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:04:42 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/11/26 16:09:59 by wdeltenr         ###   ########.fr       */
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

static int		direct_path(t_links *start)
{
	while (start)
	{
		if (start->room->index == END)
			return (1);
		start = start->next;
	}
	return (0);
}

static void		swap_rooms(t_hill *hill, t_rooms **tab, int i, int room_ind)
{
	t_rooms	*tmp;

	tmp = tab[i];
	tab[i] = tab[room_ind];
	tab[room_ind] = tmp;
	tab[i]->index = i;
	tab[room_ind]->index = room_ind;
	if (hill->end == i)
		hill->end = room_ind;
}

int				prep_suurballe(t_hill *hill, t_rooms **tab)
{
	if (hill->start == -1 || hill->end == -1)
		return (0);
	if (!ft_strcmp(tab[hill->start]->name, tab[hill->end]->name))
		return (1);
	swap_rooms(hill, tab, START, hill->start);
	swap_rooms(hill, tab, END, hill->end);
	if (direct_path(tab[0]->links))
		return (print_direct_path(tab[1]->name, hill->ants));
	if (!(hill->max_paths = max_paths(tab)))
		return (0);
	tab[START]->ants = hill->ants;
	tab[END]->ants = hill->ants;
	return (suurballe(hill, tab));
}
