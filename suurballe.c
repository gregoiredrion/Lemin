/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/14 17:18:50 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		new_weights(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	int		i;

	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->w > 0 && tab[i]->d != -1)
			{
				li->w = li->w - tab[li->room->index]->d + tab[i]->d;
			}
			li = li->next;
		}
		i++;
	}
}

static void		new_paths(t_rooms **tab)
{
	t_links *li;
	t_links *tmp;

	li = tab[0]->links;
	while (li)
	{
		printf("start - ");
		tmp = li;
		while (tmp)
		{
			if (tmp == li && tmp->w != -1)
			{
				li = li->next;
				tmp = li;
			}
			if (tmp->w == -1 && tmp->out->w != -1)
			{
				printf("%s - ", tmp->room->name);
				tmp = tmp->room->links;
			}
			else if (tmp->w == -1 && tmp->out->w == -1)
			{
				tmp->w = 0;
				tmp->out->w = 0;
			}
			tmp = tmp->next;
		}
		printf("\n");
		li = li->next;
	}
}

void	suurballe(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	t_links	*save;
	int i;

	new_weights(hill, tab);
	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		printf("\n--%s-dist: %d--\n", tab[i]->name, tab[i]->d);
		while (li)
		{
			printf("%s-%s: %d\n", tab[i]->name, tab[li->room->index]->name, li->w);
			li = li->next;
		}
		i++;
	}
	printf("\n========\n");
	dijkstra(hill, tab);
	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		printf("\n--%s-dist: %d--\n", tab[i]->name, tab[i]->d);
		while (li)
		{
			printf("%s-%s: %d\n", tab[i]->name, tab[li->room->index]->name, li->w);
			li = li->next;
		}
		i++;
	}
}
