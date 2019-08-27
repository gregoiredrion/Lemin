/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/27 15:54:56 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		init_weights(t_rooms **tab)
{
	t_links	*li;
	int		i;

	i = 0;
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->w != -1)
				li->w = 1;
			li = li->next;
		}
		i++;
	}
}

static void		new_weights(t_hill *hill, t_rooms **tab)
{
	t_links	*li;
	int		i;

	i = 0;
	init_weights(tab);
	dijkstra(hill, tab);
//	printf("INIT\n");
//	display_tab2(tab);
	printf("BEFORE weights\n");
	printf("%s & %s\n===|%d| & |%d|===\n", tab[27]->links->next->room->name, tab[35]->links->room->name, tab[27]->links->next->w, tab[35]->links->w);
	printf("\n\nw = %d - %d + %d\n\n", tab[35]->links->w, tab[27]->d, tab[35]->d);
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->w > 0) //&& tab[i]->d != -1)
				li->w = li->w - tab[li->room->index]->d + tab[i]->d;
			li = li->next;
		}
		i++;
	}
	printf("AFTER weights\n");
	printf("%s & %s\n===|%d| & |%d|===\n\n", tab[27]->links->next->room->name, tab[35]->links->room->name, tab[27]->links->next->w, tab[35]->links->w);
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

void			dijkstra(t_hill *hill, t_rooms **tab)
{
	t_links		*li;
	int			i;

	i = 0;
	printf("BEFORE dijkstra\n");
	printf("%s & %s\n=wei==|%d| & |%d|===\n=dist==|%d| & |%d|===\n", tab[27]->links->next->room->name, tab[35]->links->room->name, tab[27]->links->next->w, tab[35]->links->w, tab[27]->d, tab[35]->d);
	while (tab[i])
	{
		li = tab[i]->links;
		while (li)
		{
			if (li->w == -1 && li->out->w == -1)
			{
				li->w = 1;
				li->out->w = 1;
			}
			if (tab[i]->d + li->w < li->room->d && li->w != -1 && tab[i]->d != -1)
				li->room->d = tab[i]->d + li->w;
			li = li->next;
		}
		i++;
	}
	printf("AFTER dijkstra\n");
	printf("%s & %s\n=wei==|%d| & |%d|===\n=dist==|%d| & |%d|===\n", tab[27]->links->next->room->name, tab[35]->links->room->name, tab[27]->links->next->w, tab[35]->links->w, tab[27]->d, tab[35]->d);
}

void			suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths)
{
	t_links		*li;
	t_links		*save;
	double		turns;
	int			nb_paths;
	t_rooms		***tmp;
	int			tmp2;

	tab[hill->start]->ants = hill->ants;
	tab[hill->end]->ants = hill->ants;
	nb_paths = 1;
	hill->max_paths = max_paths(hill, tab);
	tmp2 = 0;
	while (nb_paths < hill->max_paths)
	{
	//	printf("BEFORE\n");
	//	display_tab2(tab);
		new_weights(hill, tab);
	//	printf("Weights\n");
	//	display_tab2(tab);
		dijkstra(hill, tab);
	//	printf("Dijkstra\n");
	//	display_tab2(tab);
	//	exit (0);
		printf("BEFORE find\n");
		printf("%s & %s\n===|%d| & |%d|===\n", tab[27]->links->next->room->name, tab[35]->links->room->name, tab[27]->links->next->w, tab[35]->links->w);
		if (find_path(tab, tab[hill->end], NULL) == -1)
			break ;
		printf("AFTER find\n");
		printf("%s & %s\n===%d & |%d|===\n\n", tab[27]->links->next->room->name, tab[35]->links->room->name, tab[27]->links->next->w, tab[35]->links->w);
	//	display_tab2(tab);
		if (!(tmp = all_paths(hill, tab, nb_paths + 1)))
		// write error?
			return ;
		if (hill->turns > (turns = max_turns(hill, tmp, nb_paths + 1)))
		{
			//free (paths)
			tmp2 = 0;
			paths = tmp;
			hill->turns = turns;
		}
		else
		{
			free (tmp);//meilleur free necessaire
			tmp2++;
		}
		nb_paths++;
	}
	nb_paths -= tmp2;
//	printf("Max paths == %d && paths == %d && max turns == %d\n", hill->max_paths, nb_paths, (int)hill->turns);
	new_dists(paths);
//	display_paths(hill, paths);
	move_ants(hill, paths, tab);
}
