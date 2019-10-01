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
	int i = 0;
	li = room->links;
	ft_printf("%d. %s: dist: %d (in: %d - out: %d) && used: %d && pred: %d\n", room->index, room->name, room->d, room->in, room->out, room->used, room->pred);
	while (li)
	{
			ft_printf("	%d. %s-%s: weight: %d && out: %d && dist: %d (in: %d - out: %d) && used: %d && opp used: %d && pred: %d\n", li->room->index, room->name, li->room->name, li->w, li->opp->w, li->room->d, li->room->in, li->room->out, li->used, li->opp->used, li->room->pred);
		li = li->next;
	}
	ft_printf("\n");
}

void		display_tab2(t_rooms **tab)
{
	t_links		*li;
	int			i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%d. %s: dist: %d (in: %d - out: %d) && pred: %d && used: %d\n", i, tab[i]->name, tab[i]->d, tab[i]->in, tab[i]->out, tab[i]->pred, tab[i]->used);
		li = tab[i]->links;
		while (li)
		{
			ft_printf("	%s-%s: weight: %d && out: %d && dist: %d (in: %d - out: %d) && used: %d && opp used: %d && pred: %d\n",  tab[i]->name, li->room->name, li->w, li->opp->w, li->room->d, li->room->in, li->room->out, li->used, li->opp->used, li->room->pred);
			li = li->next;
		}
		i++;
	}
	ft_printf("\n");
}
