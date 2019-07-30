/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/30 17:40:31 by wdeltenr         ###   ########.fr       */
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
				li->w = li->w - tab[li->room->index]->d + tab[i]->d;
			li = li->next;
		}
		i++;
	}
}

static int		max_paths(t_hill *hill, t_rooms **tab)
{
	int			start;
	int			end;
	t_links		*tmp;

	start = 0;
	end = 0;
	tmp = tab[hill->start]->links;
	while (tmp)
	{
		tmp = tmp->next;
		start++;
	}
	tmp = tab[hill->end]->links;
	while (tmp)
	{
		tmp = tmp->next;
		end++;
	}
	if (end < start)
		return (end);
	return (start);
}

static void		dijkstra(t_hill *hill, t_rooms **tab)
{
	t_links		*li;
	int			i;

	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->w == -1 && li->w == li->out->w)
			{
				li->w = 0;
				li->out->w = 0;
			}
			if (tab[i]->d + li->w < li->room->d && li->w != -1)
				li->room->d = tab[i]->d + li->w;
			li = li->next;
		}
		i++;
	}
}

void			suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths)
{
	t_links		*li;
	t_links		*save;
	double		turns;
	int			nb_paths;
	t_rooms		***tmp;

	tab[hill->start]->ants = hill->ants;
	tab[hill->end]->ants = hill->ants;
	nb_paths = 1;
	hill->max_paths = max_paths(hill, tab);
	while (nb_paths < hill->max_paths)
	{
		new_weights(hill, tab);
		dijkstra(hill, tab);
		if (find_path(tab, tab[hill->end], NULL) == -1)
			break ;
		if (!(tmp = all_paths(hill, tab, nb_paths + 1)))
		// write error?
			return ;
		if (hill->turns > (turns = max_turns(hill, tmp, nb_paths + 1)))
		{
			//free (paths)
			paths = tmp;
			hill->turns = turns;
		}
		else
		{
			//free tmp
			break;
		}
		nb_paths++;
	}

	//
	new_dists(paths);
	int		j = 0;
	while (paths[j])
		display_tab2(paths[j++]);
	printf("nb_paths = %d\n", nb_paths - 1);
	sort_paths(paths, 0, nb_paths - 1);
	j = 0;
	while (paths[j])
		display_tab2(paths[j++]);
	//
	move_ants(hill, paths, tab);
}
