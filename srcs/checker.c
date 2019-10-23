/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:54:04 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/23 17:21:22 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	present(t_rooms **path, t_links *li, int j)
{
	int		need;
	int		start;
	t_rooms	*room;

	start = 0;
	room = path[j];
	if (j == 0)
	{
		start = 1;
		need = 1;
	}
	else
		need = 2;
	if (need == 1)
	{
		while (room)
		{
			li = room->links;
			while (li)
			{
				if (li->room->index == 0)
					start -= 1;
				else if (li->room->index == path[j + 1]->index
					|| li->room->index == -path[j + 1]->index)
					need -= 1;
				li = li->next;
			
			}
		room = room->next;
		}
	}
	else
	{
		while (room)
		{
			li = room->links;
			while (li)
			{
				if (li->room->index == path[j + 1]->index
					|| li->room->index == path[j - 1]->index
						|| li->room->index == -path[j - 1]->index
							|| li->room->index == -path[j + 1]->index)
					need -= 1;
				li = li->next;
			}
			room = room->next;
		}
	}
	if (need != 0 || start != 0)
	{
		printf("Need: %d - start: %d - j: %d\n", need, start, j);
		display_room(path[j]);
		display_room(path[j]->next);
		printf("BAD LINKS!!\n");
		exit (0);
	}
}

void	checker_links(t_rooms ***paths)
{
	int			i;
	int			j;
	t_links		*li;

	i = 0;
	while (paths[i])
	{
		j = 0;
		while (paths[i][j + 1])
		{
			li = paths[i][j]->links;
			present(paths[i], li, j);
			j++;
		}
		i++;
	}

}

void	checker(t_rooms ***paths, t_rooms *start, t_rooms *end)
{
	int		i;
	int		j;
	char	*save;
	int		k;
	int		l;

	k = 0;
	while (paths[k])
	{
		l = 0;
		while (paths[k][l + 1])
		{
			save = paths[k][l]->name;
			i = 0;
			if (!ft_strcmp(start->name, save) | !ft_strcmp(end->name, save))
			{
				ft_printf("Start or end middle of path\n");
				exit (0);
			}
			while (paths[i])
			{
				j = 0;
				while (paths[i][j + 1])
				{
					if (i != k && l != j && !ft_strcmp(paths[i][j]->name, save))
					{
						ft_printf("DOUBLE ROOM\n");
						display_room(paths[i][j]);
						exit (0);
					}
					j++;
				}
				i++;
			}
			l++;
		}
		k++;
	}
	checker_links(paths);
}
