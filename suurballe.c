/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/06 15:02:38 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	new_weights(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	int		i;
	int		save;

	i = 0;
	init_weights(tab);
	init_dists(hill, tab);
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->w > 0 && tab[li->room->index]->d != -1)
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
			if (li->w == -1 && li->out->w == -1)
			{
				li->w = 1;
				li->out->w = 1;
			}
			if (tab[i]->d + li->w < li->room->d && li->w != -1
			&& tab[i]->d != -1 && li->room != end)
				li->room->d = tab[i]->d + li->w;
			li = li->next;
		}
		i++;
	}
}

t_rooms		***store_paths(t_hill *h, t_rooms **tab, t_rooms ***paths, int nb)
{
	t_rooms		***tmp;
	double		turns;

	if (!(tmp = all_paths(h, tab, nb + 1)))
		return (NULL);
	if (h->turns > (turns = max_turns(h, tmp, nb + 1)))
	{
		//free (paths)
		h->turns = turns;
		return (tmp);
	}
	else
		free(tmp);//meilleur free necessaire
	return (paths);
}

int			suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths)
{
	t_links		*li;
	int			nb_paths;

	nb_paths = 1;
	hill->max_paths = max_paths(hill, tab);
	while (nb_paths < hill->max_paths)
	{
		new_weights(hill, tab);
		dijkstra(hill, tab, tab[hill->end]);
		if (find_path(tab, tab[hill->end], NULL) == -1)
			break ;
		if (!(paths = store_paths(hill, tab, paths, nb_paths)))
			return (0);
		nb_paths++;
	}
	new_dists(paths);
	mmove_ants(hill, paths, tab);
	return (1);
}
