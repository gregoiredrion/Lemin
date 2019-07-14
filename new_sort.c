/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:09:33 by gdrion            #+#    #+#             */
/*   Updated: 2019/07/14 17:32:28 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	partition(t_hill *hill, t_rooms **tab, int start, int end)
{
	int pivot;
	int i;
	int j;

	j = 0;
	i = start - 1;
	pivot = tab[end]->d;
	while (j < end - 1)
	{
		if (tab[j]->d < pivot)
		{
			i++;
			swap_rooms(hill, tab, i, j);
		}
		j++;
	}
	swap_rooms(hill, tab, i + 1, end);
	return (i + 1);
}

void		q_sort(t_hill *hill, t_rooms **tab, int start, int end)
{
	int pivot;

	if (start < end)
	{
		pivot = partition(hill, tab, start, end);
		q_sort(hill, tab, start, pivot - 1);
		q_sort(hill, tab, pivot + 1, end);
	}
}
