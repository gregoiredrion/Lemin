#include "lemin.h"

void	display_paths(t_hill *hill, t_rooms ***paths)
{
	int		i = 0;
	int		j;
	while (paths[i])
	{
		j = 0;
		while (paths[i][j])
			j++;
		ft_printf("len path = %d\n", j);
		j = 0;
		ft_printf("%s", hill->rooms[hill->start]->name);
		while (paths[i][j])
		{
			ft_printf("-%s", paths[i][j]->name);
			j++;
		}
		ft_printf("\n");
		//	int r = 0;
		//	while (paths[r])
		//		display_tab2(paths[r++]);
		ft_printf("\n");
		i++;
	}
}

void	display_room(t_rooms *room)
{
	t_links		*li;

	li = room->links;
	ft_printf("%d. %s: dist: %d && used: %d && pred: %d\n", room->index, room->name, room->d, room->used, room->pred);
	while (li)
	{
		if (!room->used)
			ft_printf("	%d. %s-%s: weight: %d && out: %d && dist: %d && used: %d && opp used: %d && pred: %d\n", li->room->index, room->name, li->room->name, li->w, li->opp->w, li->room->d, li->used, li->opp->used, li->room->pred);
		else
			ft_printf("	%d. %s-%s: weight: %d && dist: %d && used: %d && pred: %d\n", li->room->index, room->name, li->room->name, li->w, li->room->d, li->used, li->room->pred);
		li = li->next;
	}
	ft_printf("\n");
}

void		display_tab2(t_rooms **tab)
{
	t_links		*li;
	t_rooms		*room;
	int			i;
	int			ay;

	i = 0;
	while (tab[i])
	{
		room = tab[i];
		ay = 0;
		if (room->next)
			ay = 1;
		while (room)
		{
			ft_printf("%d. %s: dist: %d && pred: %d && used: %d\n", room->index, room->name, room->d, room->pred, room->used);
			li = room->links;
			while (li)
			{
				if (!ay)
					ft_printf("	%6d. %s-%s: weight: %d && out: %d && dist: %d && used: %d && opp used: %d && pred: %d\n",li->room->index, room->name, li->room->name, li->w, li->opp->w, li->room->d, li->used, li->opp->used, li->room->pred);
				else
					ft_printf("	%6d. %s-%s: weight: %d && dist: %d && used: %d && pred: %d\n",li->room->index, room->name, li->room->name, li->w, li->room->d, li->used, li->room->pred);
				li = li->next;
			}
			room = room->next;
		}
		i++;
	}
	ft_printf("\n");
}
