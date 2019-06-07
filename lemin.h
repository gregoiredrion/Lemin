/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:24 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/06/07 19:17:56 by gdrion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"

typedef struct	s_links
{
	unsigned long	name;
	int				weight;
	struct s_links	*next;
}				t_links;

typedef struct	s_rooms
{
	char			*name;
	int				index;
	int				*links;
	int				ants;
	intmax_t		x;
	intmax_t		y;
	int				stend;
	struct s_rooms	*next;
}				t_rooms;

typedef struct	s_hill
{
	t_rooms			**rooms;
	int				start;
	int				end;
	int				ants;
	int				size;
}				t_hill;

/*
** stock infos anthill
*/
t_hill			*create_anthill(void);
t_rooms			*create_rooms(t_rooms *last, char *info, int stend);
int			hashmap(t_hill *anthill, t_rooms *begin);

/*
** free
*/
int				free_anthill(t_hill *anthill);

#endif
