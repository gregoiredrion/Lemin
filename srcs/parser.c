/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:06:58 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/29 12:42:14 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms	*parse_rooms(char **line, t_rooms *last)
{
	static int	check = 1;

	if ((*line)[0] != '#')
	{
		if (!(last = create_rooms(last, *line, 0)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##start") && check > 0 && (check *= -1)))
	{
		if (get_next_line(0, line) != 1)
			return (NULL);
		if (!(last = create_rooms(last, *line, 1)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##end")) && (check % 2) != 0 && (check *= 2))
	{
		if (get_next_line(0, line) != 1)
			return (NULL);
		if (!(last = create_rooms(last, *line, -1)))
			return (NULL);
	}
	return (last);
}

static t_rooms	*read_rooms(t_hill *hill, char **line)
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
			if (!(last = parse_rooms(line, last)))
				return (NULL);
			if (!begin)
				begin = last;
			hill->size++;
		}
	}
	if (!hashmap(hill, begin))
		return (NULL);
	return (last);
}

static int		read_link(t_hill *hill, char *line)
{
	int		ret;

	while (get_next_line(0, &line) == 1 && line[0] != '\0')
	{
		if (line[0] != '#')
		{
			ret = parse_links(hill, line);
			if (!ret)
				break ;
			if (ret == -1)
				return (-1);
		}
	}
	return (1);
}

int				parser(t_hill *hill, char *line)
{
	t_rooms		**tab;
	t_rooms		*last;

	if (!(last = read_rooms(hill, &line)))
		return (free_error(hill));
	if (!(tab = small_tab(hill)) || line[0] == '\0')
		return (free_error(hill));
	if (parse_links(hill, line) == -1)
		return (free_error(hill));
	read_link(hill, line);
	hill->rooms = tab;
	hill->size /= 2;
	if (prep_suurballe(hill, tab) == -1)
		return (free_error(hill));
	return (1);
}
