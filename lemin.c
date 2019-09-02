/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <wdeltenr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:32 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/02 18:28:54 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		free_error(t_hill *anthill)
{
	free_hill(anthill);
	write(2, "Error\n", 6);
	return (0);
}

static t_rooms	**small_tab(t_hill *anthill)
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

static t_rooms	*parse_rooms(char **line, t_rooms *last, char **str)
{
	if ((*line)[0] != '#' && (*line)[0] != 'L')
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

static int		parser(t_hill *hill, char *line)
{
	t_rooms		**tab;
	t_rooms		*begin;
	t_rooms		*last;
	char		*str;

	str = ft_itoa(hill->ants);
	last = NULL;
	begin = NULL;
	while (get_next_line(0, &line) == 1 && (ft_strchr((const char *)line, ' ')
	|| line[0] == '#'))
	{
		if ((line[0] == '#' && line[1] == '#') || line[0] != '#')
		{
			if (!(last = parse_rooms(&line, last, &str)))
				return (0);
			if (!begin)
				begin = last;
			hill->size++;
		}
		str = join_and_free_newline(str, line);
		//Badant car hashmap et du coup free_hill a ameliorer ou bien faire
		//Une nouvelle fonction pour free hill quand c'est la hashmap
	}
	if (!(hashmap(hill, begin)) || !(tab = small_tab(hill)) || line[0] == '\0')
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

int				main(void)
{
	char		*line;
	t_hill		*anthill;

	if (!(anthill = create_anthill()))
		return (0);
	if (get_next_line(0, &line) != 1)
		return (0);
	if ((anthill->ants = check_ants(line)) <= 0)
	{
		free(line);
		return (free_error(anthill));
	}
	free(line);
	if (!(parser(anthill, line)))
		return (free_error(anthill));
//	free_hill(anthill);
	return (0);
}
