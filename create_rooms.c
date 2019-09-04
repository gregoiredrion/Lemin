/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:47:47 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/04 16:06:03 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_rooms		*create_rooms(t_rooms *last, char *line, int stend)
{
	t_rooms		*new;
	char		**tab;

	if (!(tab = check_rooms(line)))
		return (NULL);
	if (!(new = malloc(sizeof(t_rooms))))
		return (NULL);
	if (!(new->name = ft_strdup(tab[0])))
		return (NULL);
	new->stend = stend;
	new->ants = 0;
	new->d = (stend == 1) ? 0 : -1;
	new->index = -1;
	new->links = NULL;
	if ((new->x = ft_atoi(tab[1])) > INT_MAX || new->x < INT_MIN)
		return (NULL);//error && free
	if ((new->y = ft_atoi(tab[2])) > INT_MAX || new->x < INT_MIN)
		return (NULL);//error && free
	if (last)
		last->next = new;
	new->next = NULL;
	return (new);
}
