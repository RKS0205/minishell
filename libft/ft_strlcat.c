/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:14:02 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:14:02 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	count;
	size_t	size_dst;

	count = 0;
	a = ft_strlen(dst);
	size_dst = ft_strlen(dst);
	b = ft_strlen(src);
	if (size == 0)
		return (b);
	if (size < a)
		return (b + size);
	while (src[count] != '\0' && a < size - 1)
	{
		dst[a] = src[count];
		a++;
		count++;
	}
	dst[a] = '\0';
	return (size_dst + b);
}	
