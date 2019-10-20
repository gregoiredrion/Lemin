/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/18 18:31:50 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

static int	new_paths(t_hill *hill, t_rooms **tab, t_rooms ****paths, int nb)
{
	t_rooms		***tmp;
	double		turns;
	int			i;
	t_rooms		***path;

	path = *paths;
	i = 0;
	if (!(tmp = all_paths(hill, tab, nb + 1)))
		return (-1);
	checker(tmp, tab[START], tab[END]);//DELETE AT END
	if (hill->turns > (turns = max_turns(hill, tmp, nb + 1)))
	{
		while (path[i])
			free(path[i++]);
		hill->turns = turns;
		*paths = tmp;
		return (1);
	}
	else
	{
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

int			suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths)
{
	t_links		*li;
	int			nb_paths;
	int			*pred;
	int			ret;

	nb_paths = 1;
	hill->max_paths = max_paths(hill, tab);
	display_room(tab[1]);
	while (nb_paths < hill->max_paths)
	{
		bellman_ford(tab, hill->size / 2 - 1);
		if (!find_path(tab))
			break ;
		if ((ret = new_paths(hill, tab, &paths, nb_paths)) != 1)
		{
			if (!ret)
				break ;
			return (ret);
		}
		nb_paths++;
	}
	new_dists(paths);
	//display_paths(hill, paths);
	//move_ants(hill, paths, tab);
	return (1);
}
