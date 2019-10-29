/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:56:27 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 12:50:37 by wdeltenr         ###   ########.fr       */
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
	turns = ((double)save / (double)nb_paths) - (double)1;
	return (turns);
}
