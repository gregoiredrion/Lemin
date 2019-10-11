/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:12:55 by gdrion            #+#    #+#             */
/*   Updated: 2019/10/11 14:21:29 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				find_path(t_rooms **tab, int end)
{
	t_links		*li;
	t_links		*save;
	int			pred;

	save = tab[end]->links;
	pred = tab[end]->pred;
	if (pred == -1 || tab[pred]->d == -1)
		return (0);
	while (pred != -1)
	{
		li = save;
		while (li->room->index != pred)
			li = li->next;
		pred = li->room->pred;
		save = li->room->links;
		li->opp->used = 1;
		li->w = -1;
	}
	return (1);
}
