/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:12:55 by gdrion            #+#    #+#             */
/*   Updated: 2019/08/20 15:18:28 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		update_w(t_links *li)
{
	if (li->w == -1)
	{
		li->w = 1;
		li->out->w = 1;
	}
	else
	{
		li->w = 0;
		li->out->w = -1;
	}
}

int				find_path(t_rooms **tab, t_rooms *room, t_links *out)
{
	t_links		*li;
	t_links		*save;

	if (room->index == 0)
		return (1);
	save = room->links;
	if (!save)
		return (-1);
	li = room->links;
	while (li)
	{
//		printf("%s(dist: %d)-%s(dist: %d) = w: %d\n", room->name, room->d, li->room->name, li->room->d, li->w);
		if (((li->room->d < save->room->d && li->out->w != -1) ||
		save->out->w == -1) && li != out)
			save = li;
		else if (save == out)
			save = li;
		li = li->next;
	}
//	printf("%s-%s\n", room->name, save->room->name);
	if (save->out->w == -1 || save == out)
		return (-1);
	if (find_path(tab, save->room, save->out) == -1)
		return (-1);
	update_w(save);
	return (0);
}
