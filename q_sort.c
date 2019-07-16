/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrion <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:09:33 by gdrion            #+#    #+#             */
/*   Updated: 2019/07/16 15:46:28 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	partition(t_hill *hill, t_rooms **tab, int start, int end)
{
	int pivot;
	int i;
	int j;

	i = start - 1;
	j = i + 1;
	pivot = tab[end]->d;
	while (j < end)
	{
		if (tab[j]->d <= pivot)
		{
			i++;
			swap_rooms(hill, tab, i, j);
		}
		j++;
	}
	swap_rooms(hill, tab, i + 1, end);
	return (i + 1);
}

// fix pivot

void		q_sort(t_hill *hill, t_rooms **tab, int start, int end)
{
	int pivot;

	if (end == hill->size / 2)
		return ;
	if (start < end)
	{
		pivot = partition(hill, tab, start, end);
		q_sort(hill, tab, start, pivot - 1);
		q_sort(hill, tab, pivot + 1, end);
	}
}
