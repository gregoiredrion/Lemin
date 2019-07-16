/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:24 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/16 18:19:11 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"

typedef struct	s_rooms t_rooms;

typedef struct	s_links
{
	t_rooms			*room;
	int				w;
	struct s_links	*next;
	struct s_links	*out;
}				t_links;

typedef struct	s_rooms
{
	char			*name;
	int				d;
	int				index;
	int				ants;
	intmax_t		x;
	intmax_t		y;
	int				stend;
	t_links			*links;
	struct s_rooms	*next;
}				t_rooms;

typedef struct	s_hill
{
	t_rooms			**rooms;
	int				start;
	int				end;
	int				ants;
	int				size;
	int				max_paths;
}				t_hill;

/*
** stock infos anthill
*/
unsigned int		hash(char *str, int size);
t_hill				*create_anthill(void);
t_rooms				*create_rooms(t_rooms *last, char *info, int stend);
int					hashmap(t_hill *anthill, t_rooms *begin);

/*
** free
*/
int					free_anthill(t_hill *anthill);

/*
**
*/
int					parse_links(t_hill *hill, t_rooms **tab, char *line);
void				swap_rooms(t_hill *hill, t_rooms **tab, int i, int r_ind);
void				q_sort(t_hill *hill, t_rooms **tab, int start, int end);
void				suurballe(t_hill *hill, t_rooms **tab);
void				short_path(t_hill *hill, t_rooms **tab);
int					find_path(t_rooms **tab, t_rooms *room);




void				display_tab(t_rooms **tab, int size);
void				mfpaths(t_hill *hill, t_rooms **tab);
#endif
