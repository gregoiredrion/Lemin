/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:36:47 by gdrion            #+#    #+#             */
/*   Updated: 2019/10/15 17:25:06 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		init_weights(t_rooms **tab)
{
	t_links		*li;
	int			i;

	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->w != -1)
				li->w = 1;
			li = li->next;
		}
		i++;
	}
}

void		init_dists(t_rooms **tab)
{
	int		i;

	i = 1;
	while (tab[i])
	{
		tab[i]->pred = -1;
		if (tab[i]->used)
		{
			tab[i]->next->pred = -1;
			tab[i]->next->d = -1;
		}
		tab[i++]->d = -1;
	}
}
