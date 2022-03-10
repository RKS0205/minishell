/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:13:20 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:13:20 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		count;
	char		*str;

	str = (char *)s;
	count = 0;
	while (count < n)
	{
		str[count] = c;
		count++;
	}
	return (str);
}
