/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:12:55 by gdrion            #+#    #+#             */
/*   Updated: 2019/09/04 16:59:40 by wdeltenr         ###   ########.fr       */
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

static t_links	*update_room(t_links *li, t_links *save, t_links *out)
{
	if (((li->room->d < save->room->d && li->out->w != -1) ||
	save->out->w == -1) && li != out)
		save = li;
	else if (li->room->d == save->room->d)
	{
		if (li->out->w < save->out->w)
			save = li;
	}
	else if (save == out)
		save = li;
	return (save);
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
		save = update_room(li, save, out);
		li = li->next;
	}
	if (save->out->w == -1 || save == out)
		return (-1);
	if (find_path(tab, save->room, save->out) == -1)
		return (-1);
	update_w(save);
	return (0);
}
