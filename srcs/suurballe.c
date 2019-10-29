/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:23:41 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 16:33:43 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	new_paths(t_hill *hill, t_rooms **tab, t_rooms ****paths, int nb)
{
	t_rooms		***tmp;
	t_rooms		***path;
	double		turns;
	int			i;

	i = 0;
	path = *paths;
	if (!(tmp = all_paths(tab, nb)))
		return (-1);
	if (hill->turns > (turns = max_turns(hill, tmp, nb)) || hill->turns == -1)
	{
		if (*paths)
			free_paths(*paths);
		hill->turns = turns;
		*paths = tmp;
		return (1);
	}
	free_paths(tmp);
	return (0);
}

int			suurballe(t_hill *hill, t_rooms **tab)
{
	t_rooms		***paths;
	int			nb_paths;
	int			ret;

	nb_paths = 1;
	paths = NULL;
	while (nb_paths < hill->max_paths + 1)
	{
		bellman_ford(tab, hill->size - 1);
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
	move_ants(hill, paths, tab);
	free_paths(paths);
	return (1);
}
