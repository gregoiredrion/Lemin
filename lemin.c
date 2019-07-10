/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <wdeltenr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/10 14:46:20 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	display_tab(t_rooms **tab, int size)
{
	int test = 0;
	printf("size of tab = %d\n", size);
	printf("starting display :\n\n");
	int i = 0;
	t_links	*link;

	while (i < size)
	{
		test = 0;
		printf("tab[%d]: %s(%ld, %ld) weight = %d\n", i, tab[i]->name, tab[i]->x, tab[i]->y, tab[i]->d);
		link = tab[i]->links;
		while (link)
		{
			test++;
			printf("%s-%s\n", tab[i]->name, link->room->name);
			link = link->next;
		}
		if (test == 0)
			printf("No Links\n");
		printf("\n");
		i++;
	}
}

static int		free_error(t_hill *anthill)
{
	t_hill *supprimer_cette_var;
	//free();
	supprimer_cette_var = anthill;
	write(2, "Error\n", 6);
	return (0);
}

static t_rooms		**small_tab(t_hill *anthill)
{
	t_rooms		**new;
	int			i;
	int			j;
	int			size;

	size = anthill->size / 2;
	j = 0;
	i = 0;
	if (!(new = malloc(sizeof(t_rooms *) * (size + 1))))
		return (0);
	new[size] = NULL;
	while (i < anthill->size)
	{
		if (anthill->rooms[i])
		{
			//anthill->rooms[i]->next = NULL;
			anthill->rooms[i]->index = j;
			anthill->rooms[i]->stend == -1 ? anthill->end = j : 0;
			anthill->rooms[i]->stend == 1 ? anthill->start = j : 0;
			new[j++] = anthill->rooms[i];
		}
		i++;
	}
	return (new);
}

static t_rooms	*parse_rooms(char *line, t_rooms *last)
{
	if (line[0] != '#' && line[0] != 'L')
	{
		if (!(last = create_rooms(last, line, 0)))
			return (NULL);
	}
	else if (!(ft_strcmp(line, "##start")))
	{
		free(line);
		if ((get_next_line(0, &line) != 1))
			return (NULL);
		if (!(last = create_rooms(last, line, 1)))
			return (NULL);
	}
	else if (!(ft_strcmp(line, "##end")))
	{
		free(line);
		if ((get_next_line(0, &line) != 1))
			return (NULL);
		if (!(last = create_rooms(last, line, -1)))
			return (NULL);
	}
	free(line);
	return (last);
}

static int		parser(t_hill *hill, char *line)
{
	t_rooms		**tab;
	t_rooms		*begin;
	t_rooms		*last;

	last = NULL;
	begin = NULL;
	while (get_next_line(0, &line) == 1 && (ft_strchr((const char *)line, ' ')
	|| line[0] == '#'))
	{
		if (!(last = parse_rooms(line, last)))
			return (0);
		if (!begin)
			begin = last;
		hill->size++;
	}
	//display_tab(anthill->rooms, anthill->size);
	if (!(hashmap(hill, begin)) || !(tab = small_tab(hill)) || line[0] == '\0')
		return (0);
	parse_links(hill, tab, line);
	while (get_next_line(0, &line) == 1 && line[0] != '\0')
		parse_links(hill, tab, line);
	short_path(hill, tab);
	return (1);
}

int				main(void)
{
	char		*line;
	t_hill		*anthill;

	if (get_next_line(0, &line) != 1)
		return (0);
	if (!(anthill = create_anthill()))
		return (0);
	anthill->ants = ft_atoi(line);
	free(line);
	if (!(parser(anthill, line)))
		return (free_error(anthill));
	return (0);
}
