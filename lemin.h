/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:24 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/05/30 15:13:04 by wdeltenr         ###   ########.fr       */
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
	int				*links;
	int				ants;
	intmax_t		x;
	intmax_t		y;
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
int				create_rooms(t_hill *anthill, char *info, int stend);

/*
** free
*/
int				free_anthill(t_hill *anthill);

/*
** hashmap
*/
unsigned long	hash(char *str, int size);

#endif
