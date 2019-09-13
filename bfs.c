/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:36:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/13 17:13:32 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				bfs(t_hill *hill, t_rooms **tab)
{
	t_links		*li;
	t_rooms		**queue;
	int			i;
	int			j;

	i = 0;
	if (!(queue = ft_memalloc(sizeof(t_rooms *) * (hill->size / 2 + 1))))
		return (0);
	queue[i] = tab[i];
	while (queue[i])
	{
		li = queue[i]->links;
		while (li)
		{
			j = i;
			if (li->room->d == -1)
			{
				li->room->d = queue[i]->d + 1;
				queue[j++] = li->room;
			}
		}
		i++;
	}
	free(queue);
	return (1);
}
