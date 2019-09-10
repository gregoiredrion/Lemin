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
		printf("len path = %d\n", j);
		j = 0;
		printf("%s", hill->rooms[hill->start]->name);
		while (paths[i][j])
		{
			printf("-%s", paths[i][j]->name);
			j++;
		}
		printf("\n");
		//	int r = 0;
		//	while (paths[r])
		//		display_tab2(paths[r++]);
		printf("\n");
		i++;
	}
}

void	display_room(t_rooms *room)
{
	t_links		*li;
	int i = 0;
	li = room->links;
	printf("%s: dist: %d\n", room->name, room->d);
	while (li)
	{
		printf("	%s-%s: %d\n", room->name, li->room->name, li->w);
		li = li->next;
	}
	printf("\n");
}

void		display_tab2(t_rooms **tab)
{
	t_links		*li;
	int			i;

	i = 0;
	while (tab[i])
	{
		printf("%d. %s: dist: %d\n", i, tab[i]->name, tab[i]->d);
		li = tab[i]->links;
		while (li)
		{
			printf("	%s-%s: weight: %d && dist: %d\n", tab[i]->name, li->room->name, li->w, li->room->d);
			li = li->next;
		}
		i++;
	}
	printf("\n");
}
