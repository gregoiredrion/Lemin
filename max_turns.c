/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:56:27 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/30 14:19:04 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	sum_paths(t_rooms ***paths)
{
	int		i;
	int		j;
	int		len;

	len = 0;
	i = 0;
	display_tab(paths[0], 4);
	while (paths[i])
	{
		j = 0;
		while (paths[i][j])
		{
			j++;
			len++;
		}
		i++;
	}
	return (len);
}

double		max_turns(t_hill *hill, t_rooms ***paths, int nb_paths)
{
	double		turns;
	int			save;

	save = hill->ants + sum_paths(paths);
	printf("%d + %d = %d\n", hill->ants, sum_paths(paths), save);
	turns = (double)save / (double)nb_paths - 1;
	printf("hill: %lf - new: %d / %d - 1 = %lf\n\n", hill->turns, save, nb_paths, turns);
	return (turns);
}
