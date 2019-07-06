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

int		paths(t_hill *hill, t_links *link, t_rooms *end, int len)
{
	t_links *tmp;

	tmp = link;
	if (!tmp)
	//error
		return (-1);
	if (tmp->room == end)
		return (len);
	tmp = tmp->room->links;
	return (paths(hill, tmp, end, ++len));
}

void	short_path(t_hill *hill)
{
	t_links		*start;
	t_rooms		*end;
	int			len;
	int			tmp;

	len = -1;
	start = hill->rooms[hill->start]->links;
	end = hill->rooms[hill->end];
	while (start)
	{
		if ((tmp = paths(hill, start, end, 0) < len) || len == -1)
		{
			affiche_vitfai(hill, start, end);
			len = tmp;
		}
		start = start->next;
	}
}
