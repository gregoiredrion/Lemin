/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:13:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/08/29 14:02:05 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			new_dists(t_rooms ***paths)
{
	int		i;
	int		j;

	i = 0;
	while (paths[i])
	{
		j = 0;
		while (paths[i][j])
			j++;
	printf("%d\n", j);
		paths[i][0]->d = j - 1;
		i++;
	}
	sort_paths(paths, 0, i - 1);
}

static void		swap_paths(t_rooms ***paths, int i, int j)
{
	t_rooms **tmp;

	tmp = paths[i];
	paths[i] = paths[j];
	paths[j] = tmp;
}


static int		partition(t_rooms ***paths, int start, int end)
{
	int pivot;
	int i;
	int j;

	i = start - 1;
	j = i + 1;
	pivot = paths[end][0]->d;
	while (j < end)
	{
		if (paths[j][0]->d <= pivot)
		{
			i++;
			swap_paths(paths, i, j);
		}
		j++;
	}
	swap_paths(paths, i + 1, j);
	return (i + 1);
}

void			sort_paths(t_rooms ***paths, int start, int end)
{
	int pivot;

	if (start < end)
	{
		pivot = partition(paths, start, end);
		sort_paths(paths, start, pivot - 1);
		sort_paths(paths, pivot + 1, end);
	}
}
