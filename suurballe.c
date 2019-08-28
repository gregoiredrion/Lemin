/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/28 16:19:13 by wdeltenr         ###   ########.fr       */
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
	init_dists(hill, tab, tab[hill->end]);
//	printf("INIT\n");
//	display_tab2(tab);
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

void			dijkstra(t_hill *hill, t_rooms **tab, t_rooms *end)
{
	t_links		*li;
	int			i;

	i = 0;
//	printf("=============\nENTER\n=========\n");
//	display_room(tab[50]);
//	display_room(tab[39]);
//	printf("=========\n\n");
	printf("====================\n");
	printf("==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n\n", tab[7]->name, tab[7]->d, tab[7]->links->next->w, tab[15]->name, tab[15]->d, tab[15]->links->next->w, tab[23]->name, tab[23]->d, tab[23]->links->next->w, tab[31]->name, tab[31]->d, tab[31]->links->next->w, tab[39]->name, tab[39]->d, tab[39]->links->next->w);
	printf("==%6s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n^^^^^^^^^^^^^^^^^^\n", tab[1]->name, tab[1]->d, tab[1]->links->next->w, tab[9]->name, tab[9]->d, tab[9]->links->next->w, tab[17]->name, tab[17]->d, tab[17]->links->next->w, tab[25]->name, tab[25]->d, tab[25]->links->next->w, tab[33]->name,tab[33]->d, tab[33]->links->next->w, tab[41]->name, tab[41]->d, tab[41]->links->next->w, tab[48]->name, tab[48]->d, tab[48]->links->next->w, tab[53]->name, tab[53]->d, tab[53]->links->next->w, tab[55]->name, tab[55]->d, tab[55]->links->next->w);
	while (tab[i])
	{
		if (i == hill->end)
			i++;
		li = tab[i]->links;
		while (li)
		{
	//		if (li->w == -1 && li->out->w == -1)
	//		{
	//			li->w = 1;
	//			li->out->w = 1;
	//		}
			if (tab[i]->d + li->w < li->room->d && li->w != -1
			&& tab[i]->d != -1 && li->room != end)
				li->room->d = tab[i]->d + li->w;
			li = li->next;
		}
		i++;
	}
	printf("==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n==%6s- d:%d - w:%d==\n\n", tab[7]->name, tab[7]->d, tab[7]->links->next->w, tab[15]->name, tab[15]->d, tab[15]->links->next->w, tab[23]->name, tab[23]->d, tab[23]->links->next->w, tab[31]->name, tab[31]->d, tab[31]->links->next->w, tab[39]->name, tab[39]->d, tab[39]->links->next->w);
	printf("==%6s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n==%s- d:%d - w:%d==\n^^^^^^^^^^^^^^^^^^\n", tab[1]->name, tab[1]->d, tab[1]->links->next->w, tab[9]->name, tab[9]->d, tab[9]->links->next->w, tab[17]->name, tab[17]->d, tab[17]->links->next->w, tab[25]->name, tab[25]->d, tab[25]->links->next->w, tab[33]->name,tab[33]->d, tab[33]->links->next->w, tab[41]->name, tab[41]->d, tab[41]->links->next->w, tab[48]->name, tab[48]->d, tab[48]->links->next->w, tab[53]->name, tab[53]->d, tab[53]->links->next->w, tab[55]->name, tab[55]->d, tab[55]->links->next->w);
	printf("====================\n\n\n\n\n\n\n\n");
//	printf("=========\n");
///	display_room(tab[50]);
//	display_room(tab[39]);
//	printf("=========\n\n");
}

void			suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths)
{
	t_links		*li;
	t_links		*save;
	double		turns;
	int			nb_paths;
	t_rooms		***tmp;
	int			tmp2;

//	printf("%s\n%s\n%s\n%s\n%s\n\n\n", tab[7]->links->next->room->name, tab[15]->links->next->room->name, tab[23]->links->next->room->name, tab[31]->links->next->room->name, tab[39]->links->next->room->name);
	//printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", tab[1]->links->next->room->name, tab[9]->links->next->room->name, tab[17]->links->next->room->name, tab[25]->links->next->room->name, tab[33]->links->next->room->name, tab[41]->next->links->room->name, tab[55]->links->next->room->name, tab[50]->links->next->room->name);
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
		dijkstra(hill, tab, tab[hill->end]);
	//	printf("Dijkstra\n");
	//	display_tab2(tab);
	//	exit (0);
		if (find_path(tab, tab[hill->end], NULL) == -1)
			break ;
	//	display_room(tab[hill->end]);
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
//	display_tab2(tab);
	move_ants(hill, paths, tab);
}
