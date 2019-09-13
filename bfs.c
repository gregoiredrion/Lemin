/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:36:34 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/13 14:55:34 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		bfs(t_rooms *room)
{
	t_links		*li;
	
	li = room->links;

	while (li)
	{
		while (li->w == -1)
			li = li->next;
		if (room->d + 1 < li->room->d || li->room->d == -1)
		{
			li->room->d = room->d + 1;
			bfs(li->room);
		}
		li = li->next;
	}
}
