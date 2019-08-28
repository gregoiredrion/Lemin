/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 17:30:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/28 18:34:33 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	move_to_end(t_hill *hill, t_rooms **tab, t_rooms **path)
{
	int		j;

	j = path[0]->d;
	if (j == 0 || path[j - 1]->ants != 0)
	{
		tab[hill->end]->ants--;
		printf("L%d-%s ", path[j - 1]->ants, path[j]->name);
		path[j - 1]->ants = 0;
		j--;
	}
	if (!tab[hill->end]->ants)
		return (-1);
	while (j > 0 && path[j - 1]->ants == 0)
		j--;
	return (j);
}

static int	move_to_rooms(t_rooms **path, int j)
{
	path[j]->ants = path[j - 1]->ants;
	if (path[j - 1]->ants)
		printf("L%d-%s ", path[j]->ants, path[j]->name);
	else
		return (0);
	return (1);
}

/*
** Are there still ants that need to be moved, is using this path at this
** moment the fastest way and are there leftover ants that need te be send
*/

static int	use_path(t_hill *hill, t_rooms ***paths, int i, int turns)
{
	if (!hill->rooms[0]->ants ||
	(paths[i][0]->d + turns  > (int)hill->turns &&
	(!paths[i + 1] || paths[i][0]->d != paths[0][0]->d)))
	{
		paths[i][0]->ants = 0;
		return (0);
	}
	return (1);
}

static void	move_from_start(t_hill *hill, t_rooms ***paths, int i, int turns)
{
	if (!(use_path(hill, paths, i, turns)))
		return ;
	hill->rooms[0]->ants--;
	paths[i][0]->ants = hill->ants - hill->rooms[0]->ants;
	printf("L%d-%s ", paths[i][0]->ants, paths[i][0]->name);
}

void		move_ants(t_hill *hill, t_rooms ***paths, t_rooms **tab)
{
	int				i;
	int				j;
	int				turns;

	turns = 0;
	i = 0;
	while (paths[i])
	{
		j = move_to_end(hill, tab, paths[i]);
		while (j >= 0)
		{
			if (j == 0)
				move_from_start(hill, paths, i, turns);
			else
			{
				if (!move_to_rooms(paths[i], j))
					break ;
			}
			j--;
		}
		if (!paths[++i] && tab[hill->end]->ants)
		{
			turns++;
			printf("\n");
			i = 0;
		}
	}
	printf("\n");
	printf("%d turns for %d ants\n", turns, hill->ants);
}
