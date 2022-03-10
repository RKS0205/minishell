/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:13:09 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:13:09 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	count = 0;
	while (a[count] == b[count] && count < (n - 1))
		count++;
	if (n == 0)
		return (0);
	return (a[count] - b[count]);
}
