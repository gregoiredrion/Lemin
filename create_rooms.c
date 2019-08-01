/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:47:47 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/10 13:30:10 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// J'ai géré les liens comme si les rooms devaient être composées de lettre ou chiffres
// Donc oeut etre faire la meme pour les rooms
// Pas sur que c'est la demarche a faire mais j'ai pas de pdf
/*static int	forb_char(char *coord)
{
	int		i;

	i = 0;
	if (coord[0] == '-' || coord[0] == '+')
		i++;
	if ((coord[0] == '-' || coord[0] == '+') && !coord[1])
		return (0);
	while (coord[i])
	{
		if (coord[i] >= '0' && coord[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	free_error()
{
	//free
	return (0);
}

// Surtout ça
static int	error_lemin(char **infos, t_rooms *new)
{
	if (!(infos[1]) || !(infos[2]))
		return (free_error());
	if (infos[3])
		return (free_error());
	if (!(forb_char(infos[1])) || !(forb_char(infos[2])))
		return (free_error());
	new->x = ft_atoi(infos[1]);
	new->y = ft_atoi(infos[2]); // ce sera toujours dans la range d'un int si atoi;
	// meme si atol ou atointmax peut overflow, faut proteger
	if (new->x > INT_MAX || new->x < INT_MIN
	|| new->y > INT_MAX || new->y < INT_MIN)
		return (free_error());
	return (1);
}

// wtf c'est monstrueux ça en fait
t_rooms		*create_rooms(t_rooms *last, char *info, int stend)
{
	t_rooms			*new;
	int				i;
	char			**split_info;

	i = 0;
	if (!(split_info = ft_strsplit(info, ' ')))
		return (NULL);
	if (!(new = malloc(sizeof(t_rooms))))
		return (NULL);
	if (!(error_lemin(split_info, new)))
		return (NULL);
	if (!(new->name = ft_strdup(split_info[0])))
		return (NULL);
	while (split_info[i])
		free(split_info[i++]);
	free(split_info);
	new->stend = stend;
	new->ants = 0;
	new->d = (stend == 1) ? 0 : -1;
	new->index = -1;
	new->links = NULL;
	if (last)
		last->next = new;
	new->next = NULL;
	return (new);
}*/

t_rooms		*create_rooms(t_rooms *last, char *line, int stend)
{
	t_rooms		*new;
	char 		**tab;

	if (!(tab = verif_rooms(line)))
		return (NULL);
}
