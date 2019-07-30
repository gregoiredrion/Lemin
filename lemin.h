/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:24 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/07/30 13:50:20 by wdeltenr         ###   ########.fr       */
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
	double			turns;
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
void				suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths);
void				short_path(t_hill *hill, t_rooms **tab);
int					find_path(t_rooms **tab, t_rooms *room, t_links *out);
void				sort_start(t_rooms *start);
void				move_ants(t_hill *hill, t_rooms ***paths, t_rooms **tab);
t_rooms				***all_paths(t_hill *hill, t_rooms **tab, int paths);
double				max_turns(t_hill *hill, t_rooms ***paths, int nb_paths);

//delete
void				display_tab2(t_rooms **tab);
//delete
void				display_tab(t_rooms **tab, int size);
#endif
