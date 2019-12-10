/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:38:37 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/11/28 16:12:16 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		use_path(t_hill *hill, t_rooms ***paths, int i, int lines)
{
	static int	id = 1;
	t_rooms		*start;
	int			max;

	max = hill->turns;
	start = hill->rooms[START];
	if (hill->turns > (double)(int)hill->turns)
		lines--;
	if (paths[i][0]->d + lines < max && id <= start->ants)
	{
		ft_printf("L%d-%s ", id, paths[i][0]->name);
		paths[i][0]->ants = id++;
	}
	else
		paths[i][0]->ants = 0;
}

static void		print_move(t_rooms **path, t_rooms *end, int j)
{
	while (j > 0)
	{
		if (path[j] == end)
		{
			ft_printf("L%d-%s ", path[j - 1]->ants, path[j]->name);
			end->ants--;
		}
		else
		{
			if (path[j - 1]->ants)
				ft_printf("L%d-%s ", path[j - 1]->ants, path[j]->name);
			path[j]->ants = path[j - 1]->ants;
		}
		j--;
	}
}

static int		find_empty(t_rooms **path)
{
	int		j;

	j = path[0]->d;
	while (j > 0 && !path[j - 1]->ants)
		j--;
	return (j);
}

void			move_ants(t_hill *hill, t_rooms ***paths, t_rooms **tab)
{
	int		i;
	int		lines;
	int		j;

	i = 0;
	lines = 0;
	while (paths[i])
	{
		j = find_empty(paths[i]);
		print_move(paths[i], tab[END], j);
		use_path(hill, paths, i, lines);
		if (!paths[++i] && tab[END]->ants)
		{
			i = 0;
			lines++;
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}

int				print_direct_path(char *end, int ants)
{
	int		id;

	id = 1;
	while (id <= ants)
		ft_printf("L%d-%s ", id++, end);
	ft_printf("\n");
	return (1);
}
