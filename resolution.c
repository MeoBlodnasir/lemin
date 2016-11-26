/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:42:37 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 18:14:25 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	reset_turn(t_room *rooms)
{
	t_room	*tmp;

	tmp = rooms;
	while (tmp)
	{
		tmp->moved = 0;
		tmp = tmp->next;
	}
}

void	change_values(t_room **best, t_room **tmp)
{
	(*tmp)->full -= 1;
	(*best)->full += 1;
	(*best)->ant = (*tmp)->ant;
	(*best)->moved = 1;
	if ((*tmp)->start_end == 1)
		(*tmp)->ant -= 1;
	else
		(*tmp)->ant = 0;
	ft_printf("L%d-%s ", (*best)->ant, (*best)->name);
}

void	best_move(t_connect *con, t_room *tmp)
{
	t_room	*best;
	int		move;

	move = 0	;
	best = NULL;
	while (con)
	{
		if ((con->room->full == 0 || con->room->start_end == 2) &&
				(best == NULL || (con->room->score <= best->score)))
		{
			best = con->room;
			move = 1;
		}
		con = con->next;
	}
	if (move == 1)
	{
		move = 0;
		change_values(&best, &tmp);
	}
}

void	main_loop(t_room *rooms)
{
	t_connect	*con;
	t_room		*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->start_end != 2 && tmp->full >= 1 && tmp->moved == 0)
		{
			con = tmp->connects;
			best_move(con, tmp);
		}
		tmp = tmp->next;
	}
}

void	move_ants(int nb_ants, t_room *rooms, t_room *last)
{
	int	re;

	if (init_path(rooms, nb_ants) == -1)
		return ;
	while (last->full < nb_ants)
	{
		reset_turn(rooms);
		re = nb_ants;
		while (re > 0)
		{
			main_loop(rooms);
			re--;
		}
		ft_printf("\n");
	}
}
