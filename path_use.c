/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 14:14:39 by gdrion            #+#    #+#             */
/*   Updated: 2019/09/02 18:24:38 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			check_use(t_rooms ***paths, t_hill *hill, int i, int lines)
{
	static int	id = 1;
	t_rooms		*start;
	int			max;

	max = hill->turns;
	start = hill->rooms[0];
	if (hill->turns > (double)(int)hill->turns)
		lines--;
	if ((paths[i][0]->d + lines < max || paths[i][0]->d == paths[0][0]->d)
	&& id <= start->ants)
	{
		printf("L%d-%s ", id, paths[i][0]->name);
		paths[i][0]->ants = id++;
	}
	else
		paths[i][0]->ants = 0;
}

void			room_to_room(t_rooms **path, t_hill *hill, t_rooms *end, int j)
{
	while (j > 0)
	{
		if (path[j] == end)
		{
			printf("L%d-%s ", path[j - 1]->ants, path[j]->name);
			end->ants--;
		}
		else
		{
			if (path[j - 1]->ants)
				printf("L%d-%s ", path[j - 1]->ants, path[j]->name);
			path[j]->ants = path[j  - 1]->ants;
		}
		j--;
	}
}

int			find_empty(t_rooms **path)
{
	int		j;

	j = path[0]->d;
	while (j > 0 && !path[j - 1]->ants)
		j--;
	return (j);
}

void		mmove_ants(t_hill *hill, t_rooms ***paths, t_rooms **tab)
{
	int		i;
	int		lines;
	int		j;

	printf("Max turns = %f\n", hill->turns);
	i = 0;
	lines = 0;
	while (paths[i])
	{
		j = find_empty(paths[i]);
		room_to_room(paths[i], hill, tab[hill->end], j);
		check_use(paths, hill, i, lines);
		if (!paths[++i] && tab[hill->end]->ants)
		{
			i = 0;
			printf("\n");
			lines++;
		}
	}
	printf("\n");
//	display_paths(hill, paths);
	printf("\n");
	printf("%d turns for %d ants\n", lines + 1, hill->ants);
}
