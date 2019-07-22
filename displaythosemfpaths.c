#include "lemin.h"

void			display_paths(t_rooms *room, t_rooms *end)
{
	t_links	*li;

	if (room == end)
		return ;
	li = room->links;
	while (li->w != -1)
		li = li->next;
	printf("-%s", li->room->name);
	display_paths(li->room, end);
}

static void		new_dists(t_hill *hill, t_rooms **tab)
{
	t_links		*li;
	t_links		*tmp;
	t_rooms		*prev;

	li = tab[0]->links;
	while (li)
	{
		tmp = li;
		if (tmp->w == -1)
		{
			prev = tab[0];
			while (prev != tab[hill->end])
			{
				while (tmp->w != -1)
					tmp = tmp->next;
				tmp->room->d = prev->d + 1;
				prev = tmp->room;
				tmp = prev->links;
			}
		}
		li = li->next;
	}
}

void	mfpaths(t_hill *hill, t_rooms **tab)
{
	t_links		*li;

	li = tab[0]->links;
	while (li)
	{
		if (li->w == -1)
		{
			printf("%s-%s", tab[0]->name, li->room->name);
			display_paths(li->room, tab[hill->end]);
			printf("\n");
		}
		li = li->next;
	}
	new_dists(hill, tab);
	//sort links of start by shortest paths
}
