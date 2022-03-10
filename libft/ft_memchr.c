/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:13:05 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:13:05 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*a;

	a = (unsigned char *) s;
	count = 0;
	if (n == 0)
		return (NULL);
	while (count < n - 1)
	{
		if (*a == (unsigned char) c)
			return (a);
		count++;
		a++;
	}
	if (*a == (unsigned char) c)
		return (a);
	return (NULL);
}
