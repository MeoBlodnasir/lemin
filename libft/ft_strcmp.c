/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 11:26:10 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 14:28:39 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int t;

	t = 0;
	while (s1[t] == s2[t] && s1[t])
	{
		t++;
	}
	return (s1[t] - s2[t]);
}
