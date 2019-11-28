/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:06:58 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/11/28 15:34:57 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_rooms	*parse_rooms(char **line, t_rooms *last, int *ret)
{
	static int	check = 1;

	if ((*line)[0] != '#')
		return (create_rooms(last, line, 0));
	if (!(ft_strcmp(*line, "##start") && check > 0 && (check *= -1)))
	{
		ft_strdel(line);
		if (get_next_line(0, line) != 1)
			return (NULL);
		if (!(last = create_rooms(last, line, 1)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##end")) && (check % 2) != 0 && (check *= 2))
	{
		ft_strdel(line);
		if (get_next_line(0, line) != 1)
			return (NULL);
		if (!(last = create_rooms(last, line, -1)))
			return (NULL);
	}
	else
		*ret = 0;
	return ((*ret == 0) ? NULL : last);
}

static int		free_return(char **line, t_rooms *room, int ret)
{
	t_rooms		*tmp;

	tmp = NULL;
	if (ret == 1)
		ret = -1;
	while (room)
	{
		tmp = room->next;
		room->next = NULL;
		free_room(&room);
		room = tmp;
	}
	ft_strdel(line);
	while (get_next_line(0, line))
		ft_strdel(line);
	return (ret);
}

static int		read_rooms(t_hill *hill, char **line)
{
	t_rooms	*begin;
	t_rooms *last;
	int		ret;

	begin = NULL;
	last = NULL;
	while ((ret = (get_next_line(0, line) == 1)) && (ft_strchr(*line, ' ')
	|| *line[0] == '#'))
	{
		if (*line[0] == 'L')
			return (free_return(line, begin, 0));
		if (((*line)[0] == '#' && (*line)[1] == '#') || *line[0] != '#')
		{
			if (!(last = parse_rooms(line, last, &ret)))
				return (free_return(line, begin, ret));
			(begin == NULL) ? begin = last : begin;
			hill->size++;
		}
		ft_strdel(line);
	}
	if (ret == -1)
		return (free_return(line, begin, -1));
	if (!hill->size)
		return (free_return(line, begin, 0));
	return (hashmap(hill, begin));
}

static int		read_link(t_hill *hill, char *line)
{
	int		ret;

	while ((ret = (get_next_line(0, &line) == 1)) && line[0] != '\0')
	{
		if (line[0] != '#')
		{
			ret = parse_links(hill, line);
			if (!ret)
			{
				free_return(&line, NULL, 0);
				break ;
			}
			if (ret == -1)
				return (-1);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (ret == -1)
		return (-1);
	return (1);
}

int				parser(t_hill *hill, char *line)
{
	t_rooms		**tab;
	int			ret;

	if ((ret = read_rooms(hill, &line)) == -1 || !ret)
		return (ret);
	if (!line || line[0] == '\0' || !(tab = small_tab(hill)))
		return (0);
	ret = parse_links(hill, line);
	ft_strdel(&line);
	if (ret == -1 || !ret)
	{
		free(tab);
		return (free_return(&line, NULL, ret));
	}
	if (read_link(hill, line) == -1)
	{
		free(tab);
		return (free_return(&line, NULL, ret));
	}
	free(hill->rooms);
	hill->rooms = tab;
	hill->size /= 2;
	ft_printf("\n");
	return (ret = prep_suurballe(hill, tab));
}
