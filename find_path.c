/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:12:55 by gdrion            #+#    #+#             */
/*   Updated: 2019/07/17 17:09:36 by gdrion           ###   ########.fr       */
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

/*int				find_path(t_rooms **tab, t_rooms *room)
{
	t_links	*li;
	t_links	*save;

	if (room->index == 0)
		return (1);
	save = room->links;
	if (!save)
		return (0);
	li = save->next;
	while (li)
	{
		if ((li->room->d < save->room->d && li->out->w != -1 && save->out->w != -1)
			save = li;
		li = li->next;
	}
	if (save->out->w == -1)
		return (-1);
	if (!find_path(tab, save->room))
		return (0);
	update_w(save);
	return (1);
}*/

int			find_path(t_rooms **tab, t_rooms *room)
{
	t_links	*li;
	t_links	*save;

	if (room->index == 0)
		return (1);
	save = room->links;
	if (!save)
		return (-1);
	li = save->next;
	while (li)
	{
		if ((li->room->d < save->room->d && li->out->w != -1) ||
			save->out->w != -1)
			save = li;
		li = li->next;
	}
	if (save->out->w == -1)
		return (-1);
	if (find_path(tab, save->room) == -1)
		return (-1);
	update_w(save);
	return (1);
}



