/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:51:00 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 15:54:41 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*fill_room(t_room *room, int phase, char *line)
{
	int		i;
	char	*name;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	name = ft_strsub(line, 0, i);
	room->name = ft_strtrim(name);
	if (ft_strcmp(room->name, "") == 0)
		return (return_empty(&room));
	room->full = 0;
	room->next = NULL;
	room->prev = NULL;
	if (phase == 2)
		room->score = 0;
	else
		room->score = -1;
	room->connects = NULL;
	room->start_end = phase;
	room->ant = 0;
	room->moved = 0;
	free(name);
	return (room);
}

int		make_room(t_room **rooms, char *line, int phase)
{
	t_room	*tmp;
	t_room	*room;

	tmp = *rooms;
	if (check_room(line) == -1)
		return (-1);
	room = (t_room*)malloc(sizeof(t_room));
	room = fill_room(room, phase, line);
	if (room == NULL)
		return (-1);
	if (*rooms == NULL)
	{
		*rooms = room;
		return (0);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = room;
	room->prev = tmp;
	return (0);
}

void	set_connection(t_room *tmp, t_room *tmp2)
{
	t_connect *con1;
	t_connect *con2;
	t_connect *tmpcon;

	con1 = (t_connect*)malloc(sizeof(t_connect));
	con2 = (t_connect*)malloc(sizeof(t_connect));
	con1->room = tmp2;
	con2->room = tmp;
	con1->next = NULL;
	con2->next = NULL;
	tmpcon = tmp->connects;
	if (tmp->connects == NULL)
		tmp->connects = con1;
	else
		place_con(tmpcon, con1);
	tmpcon = tmp2->connects;
	if (tmp2->connects == NULL)
		tmp2->connects = con2;
	else
		place_con(tmpcon, con2);
}

void	assign_score(t_room **rooms, int score)
{
	t_connect	*con;

	con = (*rooms)->connects;
	while (con != NULL)
	{
		if (con->room->score > score || con->room->score == -1)
		{
			con->room->score = score;
			assign_score(&con->room, score + 1);
		}
		con = con->next;
	}
}
