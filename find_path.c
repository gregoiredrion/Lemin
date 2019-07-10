/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:12:55 by gdrion            #+#    #+#             */
/*   Updated: 2019/07/10 14:23:04 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		opp_link(t_rooms *room, char *name)
{
	t_links *tmp;

	tmp = room->links;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->room->name))
		{
			tmp->w = -1;
			break ;
		}
		tmp = tmp->next;
	}
}

int				find_path(t_rooms **tab, t_rooms* room)
{
	t_links	*li;
	t_links	*save;

	if (room->index == 0)
		return (1);
	save = room->links;
	if (save)
		li = save->next;
	else
		return (0);
	while (li)
	{
		if (li->room->d < save->room->d)
			save = li;
		li = li->next;
	}
	if (!find_path(tab, save->room))
		return (0);
	opp_link(save->room, room->name);
	room->links->w = 0;
//	printf("L%s-%s\n", save->room->name, room->name);
//	printf("%d\n", room->links->w);
	return (1);
}
