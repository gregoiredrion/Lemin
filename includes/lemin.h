/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdeltenr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:01:24 by wdeltenr          #+#    #+#             */
/*   Updated: 2019/10/23 17:45:36 by wdeltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define START 0
# define END 1

typedef struct	s_rooms t_rooms;

typedef struct	s_links
{
	t_rooms			*room;
	int				w;
	int				used;
	struct s_links	*next;
	struct s_links	*opp;
}				t_links;

typedef struct	s_rooms
 {
	char			*name;
	int				d;
	int				index;
	int				ants;
	intmax_t		x;
	intmax_t		y;
	int				used;
	int				pred;
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
	int				used;
	int				size;
	double			turns;
	int				max_paths;
}				t_hill;

/*
** Stock infos anthill
*/
t_hill				*create_hill(void);
t_rooms				*create_rooms(t_rooms *last, char *info, int stend);
int					parse_links(t_hill *hill, char *line);
unsigned int		hash(char *str, int size);
int					hashmap(t_hill *anthill, t_rooms *begin);
int					parser(t_hill *hill, char *line);
void				from_map_to_tab(t_hill *hill, t_rooms **tab);
double				max_turns(t_hill *hill, t_rooms ***paths, int nb_paths);
t_rooms				***all_paths(t_rooms **tab, int paths);
t_links				*create_link(t_rooms *room, t_links *opp);
t_rooms				**small_tab(t_hill *hill);

/*
** Infos validity
*/
int					check_ants(char *line);
char				**check_links(char *line);
char				**check_rooms(char *line);
/*
**
*/
void				end_links(t_hill *hill, t_rooms **tab, t_rooms **end);
void				dead_end(t_hill *hill, t_rooms **tab);
/*
** Free
*/
void				del_link(t_links **link);
void				free_links(t_links *link);
void				free_room(t_rooms **room);
void				free_hill(t_hill *anthill);
int					free_error(t_hill *hill);

int					first_path(t_hill *hill, t_rooms **tab);
int					find_path(t_rooms **tab);



void				bellman_ford(t_rooms **tab, int size);

/*
** Suurballe
*/
int					suurballe(t_hill *hill, t_rooms **tab, t_rooms ***paths);
void				new_dists(t_rooms ***paths);
int					duplicate_rooms(t_rooms ***paths);

/*
** Move_ants
*/
void				move_ants(t_hill *hill, t_rooms ***paths, t_rooms **tab);

//delete + fonction!!
void				display_tab2(t_rooms **tab);
//delete + fonction!!
void				display_tab(t_rooms **tab, int size);
//delete + fonction!!
void				display_paths(t_hill *hill, t_rooms ***paths);
//delete + fonction!!
void				display_room(t_rooms *room);
//delete + fonction!!
void				checker(t_rooms ***paths, t_rooms *start, t_rooms *end);

#endif
