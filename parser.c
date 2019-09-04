/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:06:58 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/04 18:26:27 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//Pourquoi dans ce fichier ?
int				free_error(t_hill *hill)
{
	free_hill(hill);
	write(2, "Error\n", 6);
	return (0);
}

static t_rooms	**small_tab(t_hill *hill)
{
	t_rooms		**new;
	int			i;
	int			j;
	int			size;

	size = hill->size / 2;
	j = 0;
	i = 0;
	if (!(new = malloc(sizeof(t_rooms *) * (size + 1))))
		return (0);
	new[size] = NULL;
	while (i < hill->size)
	{
		if (hill->rooms[i])
		{
			hill->rooms[i]->next = NULL;
			hill->rooms[i]->index = j;
			hill->rooms[i]->stend == -1 ? hill->end = j : 0;
			hill->rooms[i]->stend == 1 ? hill->start = j : 0;
			new[j++] = hill->rooms[i];
		}
		i++;
	}
	return (new);
}

static t_rooms	*parse_rooms(char **line, t_rooms *last, char **str)
{
	if (*line[0] == 'L')
		return (NULL);
	if ((*line)[0] != '#')
	{
		if (!(last = create_rooms(last, *line, 0)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##start")))
	{
		*str = join_and_free_newline(*str, *line);
		if ((get_next_line(0, line) != 1))
			return (NULL);
		if (!(last = create_rooms(last, *line, 1)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##end")))
	{
		*str = join_and_free_newline(*str, *line);
		if ((get_next_line(0, line) != 1))
			return (NULL);
		if (!(last = create_rooms(last, *line, -1)))
			return (NULL);
	}
	return (last);
}

static t_rooms	*read_rooms(t_hill *hill, char **str, char **line)
{
	t_rooms	*begin;
	t_rooms *last;

	begin = NULL;
	last = NULL;
	while (get_next_line(0, line) == 1 && (ft_strchr(*line, ' ') || *line[0] == '#'))
	{
		if (((*line)[0] == '#' && (*line)[1] == '#') || *line[0] != '#')
		{
			if (!(last = parse_rooms(line, last, str)))
				return (NULL);
			if (!begin)
				begin = last;
			hill->size++;
			*str = join_and_free_newline(*str, *line);
		}
	}
	if (!hashmap(hill, begin))
		return (NULL);
	return (last);
}

static char		*read_link(t_rooms *last, char *line, char *str)
{
	return (str);
}

int				parser(t_hill *hill, char *line)
{
	t_rooms		**tab;
	t_rooms		*last;
	char		*str;

	str = ft_itoa(hill->ants);
	if (!(last = read_rooms(hill, &str, &line)))
		return (0);
	if (!(tab = small_tab(hill)) || line[0] == '\0')
		return (0);
	parse_links(hill, tab, line);
	str = join_and_free_newline(str, line);
	while (get_next_line(0, &line) == 1 && line[0] != '\0')
	{
		if (line[0] != '#')
			if (!(parse_links(hill, tab, line)))
				break ;
		str = join_and_free_newline(str, line);
	}
	//from_map_to_tab(hill, tab);
////ça fonctionne mais je sais pas pourquoi ça segfault plus tard dans ta partie
////Je crois que c'est parce que tu free les rooms
	hill->rooms = tab;
	printf("%s\n\n", str);
	short_path(hill, tab);
	return (1);
}
