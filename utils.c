/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:45:30 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 18:11:33 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*last_room(t_room *rooms)
{
	t_room	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->start_end == 2)
			return (tmp);
		tmp = tmp->next;
	}
	ft_printf("last room not found\n");
	return (NULL);
}

int		init_path(t_room *rooms, int nb_ants)
{
	t_room *tmp;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->start_end == 1)
		{
			if (tmp->score == -1)
			{
				ft_printf("No path possible\n");
				return (-1);
			}
			tmp->full = nb_ants;
			tmp->ant = nb_ants;
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		ft_printf("No start room\n");
		return (-1);
	}
	return (1);
}

void	place_con(t_connect *tmpcon, t_connect *con)
{
	while (tmpcon->next)
		tmpcon = tmpcon->next;
	tmpcon->next = con;
}

t_room	*return_empty(t_room **room)
{
	free((*room)->name);
	free(*room);
	return (NULL);
}

void	check_noroom(t_room *rooms)
{
	if (rooms == NULL)
	{
		ft_printf("No rooms\n");
		exit(0);
	}
}
