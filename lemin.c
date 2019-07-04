/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/06/10 19:19:55 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	display_tab(t_rooms **tab, int size)
{
	printf("size of tab = %d\n", size);
	printf("starting display :\n");
	int i = 0;
	while (i < size)
	{
		if (tab[i])
			printf("%d: %s[%ld, %ld]\n", i, tab[i]->name, tab[i]->x, tab[i]->y);
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
			anthill->rooms[i]->next = NULL;
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

static char		*parser(t_hill *hill, char *line)
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
			return (NULL);
		if (!begin)
			begin = last;
		hill->size++;
	}
	hashmap(hill, begin);
	display_tab(hill->rooms, hill->size);
	tab = small_tab(hill);
	display_tab(tab, hill->size/2);
//	if (!(hashmap(hill, begin)) || !(tab = small_tab(hill)) || line[0] == '\0')
//		return (NULL);
	printf("links return = %d\n", parse_links(hill, tab, line));

	/*while (get_next_line(0, &line) == 1)
	{

	}*/
		//display_tab(tab, anthill->size / 2);
	return (line);
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
	if (!(line = parser(anthill, line)))
		return (free_error(anthill));
	printf("%s\n", line);
	while (get_next_line(0, &line) == 1 && line[0] != '\0')
	{
		printf("%s\n", line);
	/*	if (line[0] != '#')
			if (!(anthill->links = create_links(anthill->links, line)))
				return (0);
		free(line);*/
	}
	//free(line);
	return (0);
}
