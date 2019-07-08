/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:23:40 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/06 16:06:38 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		affiche_vitfai(t_hill *hill, t_links *link, t_rooms *end)
{
	t_links *tmp;

	tmp = link;
	if (!tmp)
	//error
		return (-1);
	if (tmp->room == end)
	{
		printf("%s", tmp->room->name);
		return (1);
	}
	printf("%s", tmp->room->name);
	tmp = tmp->room->links;
	return (affiche_vitfai(hill, tmp, end));
}

int		paths(t_rooms *room)
{
	t_links	*links;
	t_links	*ret;
	t_links	*save;

	links = room->links;
	ret = links;
	save = links;
	while (room)
	{
		links = room->links;
		while (links)
		{
			if (links->room->len_path > room->len_path || links->room->len_path == -1)
				links->room->len_path = room->len_path + 1;
			links = links->next;
		}
		if (ret)
		{
			room = ret->room;
			ret = ret->next;
		}
		else
		{
			room = save->room->links->room;
			links = room->links;
			save = links;
		}
	}
}

void	short_path(t_hill *hill)
{
	t_rooms		*start;
	t_rooms		*end;
	int			len;
	int			tmp;

	len = -1;
	start = hill->rooms[hill->start];
	paths(start);
}
