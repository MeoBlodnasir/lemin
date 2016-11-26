/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 13:58:44 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 18:12:13 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*get_corresponding_room(t_room *rooms, char *str)
{
	t_room *tmp;

	tmp = rooms;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int		make_connect(t_room *rooms, char *line)
{
	t_room	*tmp;
	t_room	*tmp2;
	char	*str;
	char	*str2;

	if (check_names(&str, &str2, line) == -1)
		return (-1);
	tmp = get_corresponding_room(rooms, str);
	tmp2 = get_corresponding_room(rooms, str2);
	if (ft_strcmp(tmp->name, str) != 0 || ft_strcmp(tmp2->name, str2) != 0)
	{
		ft_printf("Connection doesnt correspond to any room\n");
		return (-1);
	}
	free(str);
	free(str2);
	set_connection(tmp, tmp2);
	return (0);
}

int		handle_line(t_room **rooms, int phase, char *line)
{
	if (line[0] == '#')
		return (0);
	if (ft_strchr(line, ' ') != NULL)
	{
		if (line[0] != 'L')
			return (make_room(rooms, line, phase));
	}
	else if (*rooms)
	{
		return (make_connect(*rooms, line));
	}
	else
	{
		ft_printf("No rooms\n");
		return (-1);
	}
	return (1);
}

int		solve_it(t_room *rooms, int nb_ants)
{
	t_room	*last;

	ft_printf("\n");
	if (!rooms)
		return (0);
	last = last_room(rooms);
	if (last == NULL)
		return (0);
	assign_score(&last, 1);
	move_ants(nb_ants, rooms, last);
	return (0);
}

int		main(void)
{
	t_norm	norm;

	norm.rooms = NULL;
	norm.line = NULL;
	norm.phase = 0;
	norm.nb_ants = 0;
	while (getline(&norm.line, &norm.size, stdin) != -1)
	{
		if (norm.nb_ants == 0 && norm.line[0] != '#')
		{
			if ((norm.nb_ants = check_ants(norm.line, norm.nb_ants)) == -1)
				return (0);
			continue;
		}
		if (check_phase(norm.line, &norm.phase) == 1)
			continue;
		if (handle_line(&norm.rooms, norm.phase, norm.line) == -1)
			break ;
		if (norm.line[0])
			ft_printf("%s", norm.line);
		norm.phase = 0;
	}
	ft_printf("\n");
	check_noroom(norm.rooms);
	return (solve_it(norm.rooms, norm.nb_ants));
}
