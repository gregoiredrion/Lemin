/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 17:30:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/30 17:53:04 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	help_move_ants(t_hill *hill, t_rooms **path, int j, int id, int turns)
{
	while (j > 0 && path[j - 1]->ants == 0)
		j--;
	while (j >= 0)
	{
		if (j == 0)
		{
			if (!hill->rooms[0]->ants || path[0]->d + (int)turns > (int)hill->turns)
			{
				path[j]->ants = 0;
				break ;
			}
			path[j]->ants = id++;
			hill->rooms[0]->ants--;
			printf("L%d-%s ", path[j]->ants, path[j]->name);
		}
		else
		{
			path[j]->ants = path[j - 1]->ants;
			if (path[j - 1]->ants)
				printf("L%d-%s ", path[j]->ants, path[j]->name);
			else
				break ;
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
	int				turns;

	turns = 1;
	i = 0;
	printf("turns: %lf\n", hill->turns);
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
		if (!tab[hill->end]->ants)
			break ;
		id = help_move_ants(hill, paths[i], j, id, turns);
		if (!paths[++i] && tab[hill->end]->ants)
		{
			turns++;
			printf("\n");
			i = 0;
		}
	}
	printf("\n");
}
