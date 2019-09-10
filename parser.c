/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:06:58 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/09/09 18:15:48 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
	static int	check = 1;

	if ((*line)[0] != '#')
	{
		if (!(last = create_rooms(last, *line, 0)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##start") && check > 0 && (check *= -1)))
	{
		if ((!(*str = join_and_free_newline(*str, *line)) ||
		((get_next_line(0, line) != 1))))
			return (NULL);
		if (!(last = create_rooms(last, *line, 1)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##end")) && (check % 2) != 0 && (check *= 2))
	{
		if (!(*str = join_and_free_newline(*str, *line)) ||
		((get_next_line(0, line) != 1)))
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
	while (get_next_line(0, line) == 1 && (ft_strchr(*line, ' ')
	|| *line[0] == '#'))
	{
		if (*line[0] == 'L')
			return (NULL);
		if (((*line)[0] == '#' && (*line)[1] == '#') || *line[0] != '#')
		{
			if (!(last = parse_rooms(line, last, str)))
				return (NULL);
			if (!begin)
				begin = last;
			hill->size++;
			if (!(*str = join_and_free_newline(*str, *line)))
				return (NULL);
		}
	}
	if (!hashmap(hill, begin))
		return (NULL);
	return (last);
}

static char		*read_link(t_hill *hill, t_rooms **tab, char *line, char *str)
{
	int		ret;

	while (get_next_line(0, &line) == 1 && line[0] != '\0')
	{
		if (line[0] != '#')
		{
			ret = parse_links(hill, tab, line);
			if (!ret)
				break ;
			if (ret == -1)
				return (NULL);
		}
		if (!(str = join_and_free_newline(str, line)))
			return (NULL);
	}
	return (str);
}

int				parser(t_hill *hill, char *line)
{
	t_rooms		**tab;
	t_rooms		*last;
	char		*str;
	int			ret;

	str = ft_itoa(hill->ants);
	if (!(last = read_rooms(hill, &str, &line)))
		return (free_error(hill));
	if (!(tab = small_tab(hill)) || line[0] == '\0')
		return (free_error(hill));
	ret = parse_links(hill, tab, line);
	if (ret == -1)
		return (0);
	if (ret != 0)
	{
		if (!(str = join_and_free_newline(str, line)))
			return (free_error(hill));
		if (!(str = read_link(hill, tab, line, str)))
			return (free_error(hill));
	}
	hill->rooms = tab;
	ft_printf("%s\n\n", str);
	short_path(hill, tab);
	return (1);
}
