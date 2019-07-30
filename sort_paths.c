/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:13:10 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/30 16:26:32 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		new_dists(t_hill *hill, t_rooms ***paths)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (paths[i])
	{
		len = 0;
		j = 0;
		while (paths[i][j])
		{
			len++;
			j++;
		}
		paths[i][0]->d = len + 1;
		i++;
	}
}

void		sort_paths(t_hill *hill, t_rooms ***paths)
{
	new_dists(hill, paths);
	;
}
