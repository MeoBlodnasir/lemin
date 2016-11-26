/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 19:39:37 by aduban            #+#    #+#             */
/*   Updated: 2016/11/26 14:29:56 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t v;
	size_t l;

	l = 0;
	v = ft_strlen(dest);
	while ((l < n) && src[l])
		dest[v++] = src[l++];
	dest[v] = 0;
	return (dest);
}
