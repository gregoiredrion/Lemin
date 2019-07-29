/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 17:30:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/29 16:54:09 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	help_move_ants(t_rooms **path, t_rooms **tab, int j, int id)
{
	while (j > 0 && path[j - 1]->ants == 0)
		j--;
	while (j >= 0)
	{
		if (j == 0)
		{
			if (!tab[0]->ants)
			{
				path[j]->ants = 0;
				break ;
			}
			path[j]->ants = id++;
			tab[0]->ants--;
			printf("L%d-%s ", path[j]->ants, path[j]->name);
		}
		else
		{
			path[j]->ants = path[j - 1]->ants;
			if (path[j - 1]->ants)
				printf("L%d-%s ", path[j]->ants, path[j]->name);
		}
		j--;
	}
	return (id);
}

void		move_ants(t_hill *hill, t_rooms ***paths, t_rooms **tab)
{
	static int		id = 1;
	int				i;
	int				j;
	int				ant;

	i = 0;
	while (paths[i])
	{
		j = paths[i][0]->d;
		if (j == 0 || paths[i][j - 1]->ants != 0)
		{
			tab[hill->end]->ants--;
			printf("L%d-%s ", paths[i][j - 1]->ants, paths[i][j]->name);
			paths[i][j - 1]->ants = 0;
			j--;
		}
		id = help_move_ants(paths[i], tab, j, id);
		if (!tab[hill->end]->ants)
			break ;
		i++;
	}
	printf("\n");
	if (tab[hill->end]->ants)
		move_ants(hill, paths, tab);
}
