/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:48:17 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 18:13:10 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_room(char *line)
{
	int i;
	int sp;

	i = 0;
	sp = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			sp++;
		if ((sp > 1 && !ft_isdigit(line[i]) && line[i] != ' '
					&& line[i] != '\n') || sp > 2)
		{
			ft_printf("Bad room\n");
			return (-1);
		}
		i++;
	}
	if (sp != 2)
		return (-1);
	return (0);
}

int		check_names(char **str, char **str2, char *line)
{
	char **tab;

	tab = ft_strsplit(line, '-');
	if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
	{
		ft_printf("Bad connection\n");
		return (-1);
	}
	*str = ft_strtrim(tab[0]);
	*str2 = ft_strtrim(tab[1]);
	free(tab[0]);
	free(tab[1]);
	free(tab);
	return (1);
}

int		check_ants(char *line, int nb_ants)
{
	if ((nb_ants = ft_atoi(line)) == 0)
	{
		ft_printf("No ants\n");
		return (-1);
	}
	else if (nb_ants < 0)
	{
		ft_printf("Invalid number of ants\n");
		return (-1);
	}
	ft_printf("%d\n", nb_ants);
	return (nb_ants);
}

void	err_se(int dup)
{
	if (dup > 1)
	{
		ft_printf("Mulitple start or end rooms\n");
		exit(0);
	}
}

int		check_phase(char *line, int *phase)
{
	static int start = 0;
	static int end = 0;

	if (ft_strcmp(line, "##start\n") == 0)
	{
		ft_printf("%s", line);
		*phase = 1;
		start++;
		err_se(start);
		return (1);
	}
	else if (ft_strcmp(line, "##end\n") == 0)
	{
		ft_printf("%s", line);
		*phase = 2;
		end++;
		err_se(end);
		return (1);
	}
	return (0);
}
