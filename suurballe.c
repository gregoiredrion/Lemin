/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/11 14:38:23 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	new_weights(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	int		i;
	int		save;

//	init_weights(tab);
//	init_dists(hill, tab);
	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->used)
				if ((save = li->w - tab[li->room->index]->d + tab[i]->d) >= 0)
					li->w = save;
			li = li->next;
		}
		i++;
	}
}

static int	max_paths(t_hill *hill, t_rooms **tab)
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

static void	dijkstra(t_hill *hill, t_rooms **tab, t_rooms *end)
{
	t_links		*li;
	int			i;

	i = 0;
	while (tab[i])
	{
		if (i == hill->end && !tab[++i])
			return ;
		li = tab[i]->links;
		while (li)
		{
			if (tab[i]->d + li->w < li->room->d && li->w != -1
			&& li->room != end && tab[i]->d != -1)
				li->room->d = tab[i]->d + li->w;
			li = li->next;
		}
		i++;
	}
}

//static?
t_rooms		***store_paths(t_hill *hill, t_rooms **tab, t_rooms ***paths, int nb)
{
	t_rooms		***tmp;
	double		turns;
	int			i;

	i = 0;
	if (!(tmp = all_paths(hill, tab, nb + 1)))
		return (NULL);
	if (hill->turns > (turns = max_turns(hill, tmp, nb + 1)))
	{
		while (paths[i])
			free(paths[i++]);
		hill->turns = turns;
		return (tmp);
	}
	else
	{
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
	}
	return (paths);
}

int			suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths)
{
	t_links		*li;
	int			nb_paths;
	int			*pred;

	nb_paths = 1;
	hill->max_paths = max_paths(hill, tab);
	while (nb_paths < hill->max_paths)
	{
		bellman_ford(tab, hill->size / 2 - 1);
		if (!find_path(tab, hill->end))
			break ;
		if (!(paths = store_paths(hill, tab, paths, nb_paths)))
			return (0);
		nb_paths++;
	}
	new_dists(paths);
	display_paths(hill, paths);
	checker(paths, tab[0], tab[hill->end]);
	//move_ants(hill, paths, tab);
	return (1);
}
