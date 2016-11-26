/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:27:24 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 18:11:52 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# include <stdio.h>

typedef struct			s_connect
{
	struct s_room		*room;
	struct s_connect	*next;
}						t_connect;

typedef struct			s_room
{
	int					full;
	char				*name;
	int					ant;
	int					moved;
	struct s_room		*next;
	struct s_room		*prev;
	struct s_connect	*connects;
	int					score;
	int					start_end;

}						t_room;
typedef struct			s_norm
{
	char				*line;
	size_t				size;
	int					phase;
	int					nb_ants;
	t_room				*rooms;
}						t_norm;

void					move_ants(int nb_ants, t_room *rooms, t_room *last);
int						init_path(t_room *rooms, int nb_ants);
t_room					*return_empty(t_room **room);
void					place_con(t_connect *tmpcon, t_connect *con);
t_room					*last_room(t_room *rooms);
int						check_ants(char *line, int nb_ants);
int						check_phase(char *line, int *phase);
int						check_names(char **str, char **str2, char *line);
int						check_room(char *line);
void					assign_score(t_room **rooms, int score);
void					set_connection(t_room *tmp, t_room *tmp2);
int						make_room(t_room **rooms, char *line, int phase);
void					check_noroom(t_room *rooms);
#endif
