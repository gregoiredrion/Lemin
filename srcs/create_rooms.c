/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:47:47 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 15:00:33 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms	*free_tab(char **tab, t_rooms *room, char **line, t_rooms *ret)
{
	int			i;

	i = 0;
	ft_strdel(line);
	if (room)
		free_room(&room);
	while (tab && tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	return (ret);
}

t_rooms			*create_rooms(t_rooms *last, char **line, int stend)
{
	t_rooms		*new;
	char		**tab;

	if (!(tab = check_rooms(*line)))
		return (NULL);
	if (!(new = malloc(sizeof(t_rooms))))
		return (free_tab(tab, NULL, line, NULL));
	if (!(new->name = ft_strdup(tab[0])))
		return (free_tab(tab, new, line, NULL));//free new
	new->stend = stend;
	new->ants = 0;
	new->d = (stend == 1) ? 0 : -1;
	new->index = -1;
	new->used = 0;
	new->pred = -1;
	new->links = NULL;
	new->next = NULL;
	if ((new->x = ft_atoi(tab[1])) > INT_MAX || new->x < INT_MIN)
		return (free_tab(tab, new, line, NULL));
	if ((new->y = ft_atoi(tab[2])) > INT_MAX || new->x < INT_MIN)
		return (free_tab(tab, new, line, NULL));
	if (last)
		last->next = new;
	return (free_tab(tab, NULL, line, new));
}
