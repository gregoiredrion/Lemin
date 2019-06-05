/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/06/05 16:43:33 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		free_error(t_hill *anthill)
{
	t_hill *supprimer_cette_var;
	//free();
	supprimer_cette_var = anthill;
	write(2, "Error\n", 6);
	return (0);
}

static int		small_tab(t_hill *anthill)
{
	t_rooms		**new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(new = malloc(sizeof(t_rooms *) * (anthill->size / 2))))
		return (0);
	while (i < anthill->size)
	{
		if (anthill->rooms[i])
			new[j++] = anthill->rooms[i];
		//free(anthill->rooms[i]);
		anthill->rooms[i] = NULL;
		i++;
	}
	//free(anthill->rooms);
	anthill->rooms = NULL;
	anthill->rooms = new;
	return (1);
}

static char		*rooms(t_hill *anthill, char *line)
{
	t_rooms		*begin;
	t_rooms		*last;

	last = NULL;
	begin = NULL;
	while (get_next_line(0, &line) == 1 && (ft_strchr((const char *)line, ' ')
	|| line[0] == '#'))
	{
		if (line[0] != '#')
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
		if (!(begin))
			begin = last;
		anthill->size++;
	}
	hashmap(anthill, begin);
	small_tab(anthill);
	if (!small_tab(anthill) || line[0] == '\0')
		return (NULL);
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
	if (!(line = rooms(anthill, line)))
		return (free_error(anthill));
	int i = 0;
	while (anthill->rooms[i])
	{
		printf("%d: %s[%ld, %ld]\n", i, anthill->rooms[i]->name, anthill->rooms[i]->x, anthill->rooms[i]->y);
		i++;
	}
//	printf("start = %d & end = %d\nstart->name = %s & end->name: %s\n", anthill->start, anthill->end, anthill->rooms[anthill->start]->name, anthill->rooms[anthill->end]->name);
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
