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
}
