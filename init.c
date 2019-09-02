/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:36:47 by gdrion            #+#    #+#             */
/*   Updated: 2019/09/02 15:59:08 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		init_dists(t_hill *hill, t_rooms **tab)
{
	int		i;
	t_links	*li;

	i = 1;
	while (tab[i])
		tab[i++]->d = -1;
	i = 0;
	while (tab[i])
	{
		if (i == hill->end)
			i++;
		li = tab[i]->links;
		while (li)
		{
			if (((tab[i]->d + li->w < li->room->d) ||
			li->room->d == -1) && tab[i]->d != -1)
				li->room->d = tab[i]->d + 1;
			li = li->next;
		}
		i++;
	}
}
