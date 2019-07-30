/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:13:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/30 17:20:23 by gdrion           ###   ########.fr       */
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
		paths[i][0]->d = j;
		i++;
	}
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
	printf("pret\n");
	int pivot;
	int i;
	int j;

	i = start - 1;
	j = i + 1;
	pivot = paths[end][0]->d;
	printf("pivot = %d\n", pivot);
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

	printf("prout\n");
	if (start < end)
	{
		pivot = partition(paths, start, end);
		sort_paths(paths, start, pivot - 1);
		sort_paths(paths, pivot + 1, end);
	}
}
