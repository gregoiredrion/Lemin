#include "lemin.h"

static void		del_link(t_links **link)
{
	t_links	*li;

	li = *link;
	li->room = NULL;
	li->w = 0;
	li->next = NULL;
	li->out = NULL;
	ft_memdel((void **)link);
}

static void		free_links(t_links *links)
{
	t_links *tmp;

	while (links)
	{
		tmp = links;
		links = links->next;
		del_link(&tmp);
	}
}

void			free_room(t_rooms **r)
{
	t_rooms	*room;

	room = *r;
	ft_strdel(&(room->name));
	room->d = 0;
	room->index = 0;
	room->ants = 0;
	room->x = 0;
	room->y = 0;
	room->stend = 0;
	free_links(room->links);
	room->links = NULL;
	room->next = NULL;
	ft_memdel((void **)r);
}

void			free_hill(t_hill *hill)
{
	int		i;
	t_rooms	**tab;

	i = 0;
	tab = hill->rooms;
	while (i < hill->size)
	{
		if (tab[i])
		{
			free_room(&tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	hill->rooms = NULL;
	hill->start = 0;
	hill->end = 0;
	hill->ants = 0;
	hill->size = 0;
	hill->turns = 0;
	hill->max_paths = 0;
	ft_memdel((void **)&tab);
	ft_memdel((void **)&hill);
}
